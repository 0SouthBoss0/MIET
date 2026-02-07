import java.io.BufferedReader;
import java.io.FileReader;
import java.util.*;

public class MagazineAutomation {
    private final Set<String> states = new HashSet<>();
    private final Set<String> inputAlphabet = new HashSet<>();
    private final Set<String> stackAlphabet = new HashSet<>();
    private final String startState = "s0";
    private final String startStackSymbol = "h0";
    private final Set<String> finalStates = new HashSet<>();
    private final List<Command> commands = new ArrayList<>();
    private final Map<String, List<String>> grammarRules = new HashMap<>();

    public static class AcceptanceResult {
        public boolean accepted;
        public List<String> configurations;

        public AcceptanceResult(boolean accepted, List<String> configurations) {
            this.accepted = accepted;
            this.configurations = configurations;
        }
    }

    public void buildFromGrammar(String grammarFile) throws Exception {
        states.add("s0");
        finalStates.add("s0");
        stackAlphabet.add("h0");

        // Чтение грамматики из файла
        BufferedReader reader = new BufferedReader(new FileReader(grammarFile));
        String line;

        while ((line = reader.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) continue;

            // Разделяем левую и правую части
            String[] parts = line.split(">", 2);
            if (parts.length < 2) continue;

            String leftPart = parts[0].trim();
            String rightParts = parts[1].trim();

            // Добавляем нетерминал в алфавит магазина
            stackAlphabet.add(leftPart);

            // Разделяем альтернативные правые части
            String[] alternatives = rightParts.split("\\|");

            for (String alt : alternatives) {
                alt = alt.trim();
                if (!alt.isEmpty()) {
                    // Добавляем правило грамматики
                    if (!grammarRules.containsKey(leftPart)) {
                        grammarRules.put(leftPart, new ArrayList<>());
                    }
                    grammarRules.get(leftPart).add(alt);

                    // Добавляем символы в алфавиты
                    for (char c : alt.toCharArray()) {
                        String symbol = String.valueOf(c);
                        if (Character.isUpperCase(c)) {
                            stackAlphabet.add(symbol); // Нетерминал
                        } else {
                            inputAlphabet.add(symbol); // Терминал
                            stackAlphabet.add(symbol); // Терминал также в алфавите магазина
                        }
                    }
                }
            }
        }
        reader.close();

        // Построение команд типа (1) - для нетерминалов
        for (Map.Entry<String, List<String>> entry : grammarRules.entrySet()) {
            String nonTerminal = entry.getKey();
            for (String production : entry.getValue()) {
                // Правильный реверс - меняем порядок символов
                StringBuilder result = new StringBuilder();
                for (char c : production.toCharArray()) {
                    switch (c) {
                        case '(' -> result.append(')');
                        case ')' -> result.append('(');
                        case '{' -> result.append('}');
                        case '}' -> result.append('{');
                        default -> result.append(c);
                    }
                }
                production = result.toString();
                String reversedProduction = reverseProduction(production);
                commands.add(new Command("s0", "λ", nonTerminal, "s0", reversedProduction));
            }
        }

        // Построение команд типа (2) - для терминалов
        for (String terminal : inputAlphabet) {
            if (!terminal.equals("λ")) {
                commands.add(new Command("s0", terminal, terminal, "s0", "λ"));
            }
        }

        // Команда типа (3) - переход в конечное состояние
        commands.add(new Command("s0", "λ", "h0", "s0", "λ"));
    }

    // Метод для правильного реверса продукции
    private String reverseProduction(String production) {
        return new StringBuilder(production).reverse().toString();
    }

    public AcceptanceResult acceptsWithTrace(String input, boolean showTrace) {
        List<String> configurations = new ArrayList<>();

        // Начальная конфигурация: (s0, input, h0E)
        String initialStack = startStackSymbol + "E";
        configurations.add(String.format("(s0, %s, %s)",
                input.isEmpty() ? "λ" : input,
                initialStack));

        boolean result = dfs("s0", input, initialStack, configurations, new HashSet<>(), 0);

        return new AcceptanceResult(result, configurations);
    }

    private boolean dfs(String state, String input, String stack, List<String> configurations,
                        Set<String> visited, int depth) {
        // Ограничение глубины для избежания бесконечной рекурсии
        if (depth > 50) {
            return false;
        }

        String visitedKey = state + "|" + input + "|" + stack;
        if (visited.contains(visitedKey)) {
            return false;
        }
        visited.add(visitedKey);

        // Проверка заключительной конфигурации
        if (state.equals("s0") && input.isEmpty() && stack.equals("h0")) {
            configurations.add("(s0, λ, λ)");
            return true;
        }

        // Пробуем все возможные команды
        for (Command cmd : commands) {
            if (!cmd.state.equals(state)) continue;

            // Проверяем входной символ
            boolean inputMatch;
            if (cmd.inputSymbol.equals("λ")) {
                inputMatch = true;
            } else {
                inputMatch = !input.isEmpty() &&
                        cmd.inputSymbol.equals(String.valueOf(input.charAt(0)));
            }

            // Проверяем символ в вершине стека
            boolean stackMatch = !stack.isEmpty();
            String topStackSymbol = "";
            if (stackMatch) {
                topStackSymbol = String.valueOf(stack.charAt(stack.length() - 1));
                stackMatch = topStackSymbol.equals(cmd.stackSymbol);
            }

            if (inputMatch && stackMatch) {
                // Новая входная строка
                String newInput = cmd.inputSymbol.equals("λ") ?
                        input : input.substring(1);

                // Новое содержимое стека
                String newStack = stack.substring(0, stack.length() - 1);
                if (!cmd.newStackSymbols.equals("λ")) {
                    newStack += cmd.newStackSymbols;
                }

                // Новая конфигурация
                String newState = cmd.newState;
                String newConfig = String.format("(%s, %s, %s)",
                        newState,
                        newInput.isEmpty() ? "λ" : newInput,
                        newStack.isEmpty() ? "λ" : newStack);

                configurations.add(newConfig);

                if (dfs(newState, newInput, newStack, configurations, visited, depth + 1)) {
                    return true;
                }

                // Откат - удаляем последнюю конфигурацию если путь не ведет к успеху
                configurations.remove(configurations.size() - 1);
            }
        }

        return false;
    }

    public void printAutomatonInfo() {
        System.out.println("=== ИНФОРМАЦИЯ О АВТОМАТЕ ===");

        System.out.println("Множество состояний S: " + states);
        System.out.println("Входной алфавит P: " + inputAlphabet);
        System.out.println("Алфавит магазина Z: " + stackAlphabet);
        System.out.println("Начальное состояние: " + startState);
        System.out.println("Начальный символ магазина: " + startStackSymbol);
        System.out.println("Заключительные состояния F: " + finalStates);

        System.out.println("\n=== КОМАНДЫ АВТОМАТА ===");
        // Сортируем команды для лучшей читаемости
        commands.sort(Comparator.comparing((Command c) -> c.stackSymbol).thenComparing(c -> c.inputSymbol));

        for (Command cmd : commands) {
            System.out.println(cmd);
        }
        System.out.println();
    }
}

// Вспомогательный класс для хранения конфигураций
class Configuration {
    String state;
    String input;
    String stack;

    Configuration(String state, String input, String stack) {
        this.state = state;
        this.input = input;
        this.stack = stack;
    }
}

