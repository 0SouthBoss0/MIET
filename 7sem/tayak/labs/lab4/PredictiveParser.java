import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

class PredictiveParser {
    private final Grammar grammar;
    private final Map<String, Map<String, List<String>>> parsingTable;
    private final Map<String, Set<String>> syncTokens; // Синхронизирующие токены
    private Stack<String> stack;
    private List<String> inputTokens;
    private int currentTokenIndex;

    public PredictiveParser(Grammar grammar, Map<String, Map<String, List<String>>> parsingTable) {
        this.grammar = grammar;
        this.parsingTable = parsingTable;
        this.syncTokens = PredictiveParserTable.computeSyncTokens(grammar, PredictiveParserTable.computeFollow(grammar, PredictiveParserTable.computeFirst(grammar)));
    }

    public List<String> tokenize(String input) {
        List<String> tokens = new ArrayList<>();
        StringBuilder currentToken = new StringBuilder();
        boolean inQuotes = false;
        char quoteChar = '\0';
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (inQuotes) {
                currentToken.append(c);
                if (c == quoteChar) {
                    inQuotes = false;
                    tokens.add(currentToken.toString());
                    currentToken.setLength(0);
                }
                continue;
            }

            if (c == '\'' || c == '"') {
                if (currentToken.length() > 0) {
                    tokens.add(currentToken.toString());
                    currentToken.setLength(0);
                }
                inQuotes = true;
                quoteChar = c;
                currentToken.append(c);
                continue;
            }

            if (Character.isWhitespace(c)) {
                if (currentToken.length() > 0) {
                    tokens.add(currentToken.toString());
                    currentToken.setLength(0);
                }
                tokens.add(" ");
                continue;
            }
            if (isSpecialCharacter(c)) {
                if (currentToken.length() > 0) {
                    tokens.add(currentToken.toString());
                    currentToken.setLength(0);
                }
                if (i + 1 < input.length()) {
                    String twoChar = "" + c + input.charAt(i + 1);
                    if (isTwoCharOperator(twoChar)) {
                        tokens.add(twoChar);
                        i++;
                        continue;
                    }
                }
                tokens.add(String.valueOf(c));
                continue;
            }
            currentToken.append(c);
        }

        if (currentToken.length() > 0) {
            tokens.add(currentToken.toString());
        }
        List<String> result = new ArrayList<>();
        for (String token : tokens) {
            if (!token.trim().isEmpty()) {
                result.add(token);
            }
        }
        // маркер конца входной строки
        result.add("$");
        return result;
    }

    private boolean isSpecialCharacter(char c) {
        return c == '(' || c == ')' || c == '{' || c == '}' ||
                c == ';' || c == '=' || c == '<' || c == '>' ||
                c == '!' || c == '\'' || c == '"' || c == '+';
    }

    private boolean isTwoCharOperator(String str) {
        return str.equals("==") || str.equals("!=");
    }

    // Сопоставление токенов с терминалами грамматики
    private String mapTokenToTerminal(String token) {
        if (token.equals("main")) return "MAIN";
        if (token.equals("int")) return "INT";
        if (token.equals("bool")) return "BOOL";
        if (token.equals("void")) return "VOID";
        if (token.equals("for")) return "FOR";
        if (token.equals("if")) return "IF";
        if (token.equals("return")) return "RETURN";
        if (token.equals("(")) return "LPAREN";
        if (token.equals(")")) return "RPAREN";
        if (token.equals("{")) return "LBRACE";
        if (token.equals("}")) return "RBRACE";
        if (token.equals(";")) return "SEMICOLON";
        if (token.equals("=")) return "ASSIGN";
        if (token.equals("<")) return "LT";
        if (token.equals(">")) return "GT";
        if (token.equals("==")) return "EQ";
        if (token.equals("!=")) return "NE";
        if (token.equals("+")) return "PLUS";
        if (token.matches("\\d+")) return "NUMBER";
        if (token.matches("[a-zA-Z_][a-zA-Z0-9_]*")) return "IDENTIFIER";
        return token;
    }

    // Восстановление ошибок в режиме паники
    private boolean panicModeRecovery(String currentToken) {
        System.out.println("АКТИВАЦИЯ РЕЖИМА ПАНИКИ");

        // пропускаем токены до синхронизирующего
        while (currentTokenIndex < inputTokens.size()) {
            String token = inputTokens.get(currentTokenIndex);
            // проверяем, является ли текущий токен синхронизирующим для верхнего элемента стека
            if (!stack.isEmpty()) {
                String top = stack.peek();
                if (grammar.nonTerminals.contains(top)) {
                    Set<String> syncSet = syncTokens.get(top);
                    if (syncSet != null && syncSet.contains(token)) {
                        System.out.println("Найден синхронизирующий токен '" + token + "' для нетерминала '" + top + "'");
                        stack.pop();
                        return true;
                    }
                }
            }
            System.out.println("Пропуск токена: '" + token + "'");
            currentTokenIndex++;
            if (currentTokenIndex >= inputTokens.size()) {
                break;
            }
        }
        return false;
    }

    public boolean parse(String input) {
        List<String> rawTokens = tokenize(input);
        inputTokens = new ArrayList<>();

        for (String token : rawTokens) {
            String terminal = mapTokenToTerminal(token);
            inputTokens.add(terminal);
        }
        System.out.println("Токенизированная входная строка: " + inputTokens);

        stack = new Stack<>();
        stack.push("$");
        // Стартовый символ
        stack.push("program");

        currentTokenIndex = 0;
        String currentToken = inputTokens.get(currentTokenIndex);

        System.out.println("\nНачало синтаксического анализа:");
        System.out.println("Стек: " + stack);
        System.out.println("Текущий токен: " + currentToken);

        int errorCount = 0;

        while (!stack.isEmpty()) {
            String top = stack.peek();

            if (grammar.terminals.contains(top)) {
                if (top.equals(currentToken)) {
                    stack.pop();
                    currentTokenIndex++;
                    if (currentTokenIndex < inputTokens.size()) {
                        currentToken = inputTokens.get(currentTokenIndex);
                    } else {
                        currentToken = "$";
                    }
                    System.out.println("Совпадение терминала: " + top);
                    System.out.println("Стек: " + stack + ", Текущий токен: " + currentToken);
                } else {
                    errorCount++;
                    System.out.println("ОШИБКА: ожидался '" + top + "', но получен '" + currentToken + "'");

                    // Восстановление ошибок
                    if (!panicModeRecovery(currentToken)) {
                        System.out.println("Не удалось восстановиться после ошибки");
                        return false;
                    }

                    if (currentTokenIndex < inputTokens.size()) {
                        currentToken = inputTokens.get(currentTokenIndex);
                    } else {
                        currentToken = "$";
                    }
                    System.out.println("Продолжение анализа после восстановления. Текущий токен: " + currentToken);
                }
            } else if (grammar.nonTerminals.contains(top) || top.equals("program")) {
                // Верхний элемент стека - нетерминал
                Map<String, List<String>> row = parsingTable.get(top);
                if (row != null) {
                    List<String> production = row.get(currentToken);

                    if (production != null) {
                        stack.pop();
                        // Добавляем символы продукции в стек в обратном порядке
                        for (int i = production.size() - 1; i >= 0; i--) {
                            String symbol = production.get(i);
                            if (!symbol.equals("ε")) { // Пропускаем epsilon-продукции
                                stack.push(symbol);
                            }
                        }
                        System.out.println("Применена продукция: " + top + " → " +
                                (production.isEmpty() ? "ε" : String.join(" ", production)));
                        System.out.println("Стек: " + stack + ", Текущий токен: " + currentToken);
                    } else {
                        // Проверяем наличие синхронизирующих токенов
                        if (row.containsKey("synch")) {
                            errorCount++;
                            System.out.println("ОШИБКА: нет продукции для [" + top + ", " + currentToken + "], используется синхронизация");
                            stack.pop(); // Синхронизация - извлекаем нетерминал
                            System.out.println("Извлечен нетерминал '" + top + "' из стека (синхронизация)");
                        } else {
                            errorCount++;
                            System.out.println("ОШИБКА: нет продукции для [" + top + ", " + currentToken + "]");

                            // Восстановление ошибок
                            if (!panicModeRecovery(currentToken)) {
                                System.out.println("Не удалось восстановиться после ошибки");
                                return false;
                            }

                            if (currentTokenIndex < inputTokens.size()) {
                                currentToken = inputTokens.get(currentTokenIndex);
                            } else {
                                currentToken = "$";
                            }
                        }
                    }
                } else {
                    errorCount++;
                    System.out.println("ОШИБКА: нет строки для нетерминала '" + top + "' в таблице разбора");
                    return false;
                }
            } else {
                errorCount++;
                System.out.println("ОШИБКА: неизвестный символ в стеке: '" + top + "'");
                return false;
            }
        }

        // Проверяем, что все токены обработаны
        boolean success = currentToken.equals("$") && stack.isEmpty();
        if (success) {
            System.out.println("\nСинтаксический анализ завершен успешно!");
            if (errorCount > 0) {
                System.out.println("Обнаружено ошибок: " + errorCount);
            }
        } else {
            System.out.println("\nОШИБКА: не все токены обработаны");
            errorCount++;
        }

        System.out.println("Всего ошибок: " + errorCount);
        return success && errorCount == 0;
    }

    // Метод для проверки файла
    public boolean parseFile(String filename) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(filename));
        StringBuilder content = new StringBuilder();
        String line;

        while ((line = reader.readLine()) != null) {
            content.append(line).append("\n");
        }
        reader.close();

        String input = content.toString().trim();
        System.out.println("Входная программа:\n" + input);
        System.out.println("\n" + "=".repeat(50));

        return parse(input);
    }

    public static void main(String[] args) {
        try {
            // чтение грамматики из файла
            Grammar grammar = PredictiveParserTable.readGrammar("src/grammar1.txt");

            // построение таблицы синтаксического анализа
            Map<String, Map<String, List<String>>> parsingTable = PredictiveParserTable.buildParsingTable(grammar);

            // вывод информации о грамматике и таблице (опционально)
            Map<String, Set<String>> first = PredictiveParserTable.computeFirst(grammar);
            Map<String, Set<String>> follow = PredictiveParserTable.computeFollow(grammar, first);
            PredictiveParserTable.printFirstAndFollow(grammar, first, follow);
            PredictiveParserTable.printParsingTable(grammar, parsingTable);

            System.out.println("\n" + "=".repeat(50));
            System.out.println("ПРОВЕРКА СИНТАКСИЧЕСКОГО АНАЛИЗАТОРА");
            System.out.println("=".repeat(50));

            PredictiveParser parser = new PredictiveParser(grammar, parsingTable);

            // Проверка входного файла
            boolean result = parser.parseFile("src/input.txt");

            if (result) {
                System.out.println("\n✓ Входной файл соответствует грамматике!");
            } else {
                System.out.println("\n✗ Входной файл не соответствует грамматике!");
            }

        } catch (IOException e) {
            System.err.println("Ошибка чтения файла: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Ошибка во время синтаксического анализа: " + e.getMessage());
            e.printStackTrace();
        }
    }
}