import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Stack;

public class CBASInterpreter {
    private String program;
    private int pos;
    private int currentToken;
    private String tokenValue;
    private Map<String, Integer> variables;
    private Stack<ForState> forStack;
    private Scanner scanner;

    private static final Map<String, Integer> KEYWORDS = new HashMap<>();

    static {
        KEYWORDS.put("print", Token.PRINT);
        KEYWORDS.put("scan", Token.SCAN);
        KEYWORDS.put("for", Token.FOR);
        KEYWORDS.put("if", Token.IF);
        KEYWORDS.put("else", Token.ELSE);
        KEYWORDS.put("to", Token.TO);
    }

    public CBASInterpreter(String program) {
        this.program = program;
        this.pos = 0;
        this.variables = new HashMap<>();
        this.forStack = new Stack<>();
        this.scanner = new Scanner(System.in);
        this.tokenValue = "";
    }

    // Лексический анализатор - получение следующей лексемы
    private int getNextToken() {
        // Пропускаем пробельные символы
        while (pos < program.length() && Character.isWhitespace(program.charAt(pos))) {
            pos++;
        }

        if (pos >= program.length()) {
            tokenValue = "";
            return Token.END;
        }

        char ch = program.charAt(pos);

        // Идентификаторы и ключевые слова
        if (Character.isLetter(ch) || ch == '_') {
            StringBuilder sb = new StringBuilder();
            while (pos < program.length() &&
                    (Character.isLetterOrDigit(program.charAt(pos)) || program.charAt(pos) == '_')) {
                sb.append(program.charAt(pos));
                pos++;
            }
            tokenValue = sb.toString();
            return KEYWORDS.getOrDefault(tokenValue, Token.IDENTIFIER);
        }

        // Числа
        if (Character.isDigit(ch)) {
            StringBuilder sb = new StringBuilder();
            while (pos < program.length() && Character.isDigit(program.charAt(pos))) {
                sb.append(program.charAt(pos));
                pos++;
            }
            tokenValue = sb.toString();
            return Token.NUMBER;
        }

        // Строки
        if (ch == '"') {
            StringBuilder sb = new StringBuilder();
            pos++; // Пропускаем открывающую кавычку
            while (pos < program.length() && program.charAt(pos) != '"') {
                sb.append(program.charAt(pos));
                pos++;
            }
            if (pos < program.length() && program.charAt(pos) == '"') {
                pos++; // Пропускаем закрывающую кавычку
            }
            tokenValue = sb.toString();
            return Token.STRING;
        }

        // Операторы и символы
        tokenValue = String.valueOf(ch);
        pos++;

        switch (ch) {
            case '+':
                return Token.PLUS;
            case '-':
                return Token.MINUS;
            case '*':
                return Token.MULTIPLY;
            case '/':
                return Token.DIVIDE;
            case '(':
                return Token.LPAREN;
            case ')':
                return Token.RPAREN;
            case '=':
                if (pos < program.length() && program.charAt(pos) == '=') {
                    pos++;
                    tokenValue = "==";
                    return Token.EQUAL;
                }
                return Token.ASSIGN;
            case '<':
                return Token.LESS;
            case '>':
                return Token.GREATER;
            case '!':
                if (pos < program.length() && program.charAt(pos) == '=') {
                    pos++;
                    tokenValue = "!=";
                    return Token.NOT_EQUAL;
                }
                break;
            case '{':
                return Token.LBRACE;
            case '}':
                return Token.RBRACE;
            case ';':
                return Token.SEMICOLON;
            case ',':
                return Token.COMMA;
        }

        return Token.UNKNOWN;
    }

    // Получить переменную (создать если не существует)
    private int getVariable(String name) {
        return variables.getOrDefault(name, 0);
    }

    // Установить значение переменной
    private void setVariable(String name, int value) {
        variables.put(name, value);
    }

    // Анализ и вычисление выражения
    private int expression() {
        int result = term();

        while (currentToken == Token.PLUS || currentToken == Token.MINUS) {
            int op = currentToken;
            currentToken = getNextToken();
            int termValue = term();

            if (op == Token.PLUS) {
                result += termValue;
            } else {
                result -= termValue;
            }
        }

        return result;
    }

    private int term() {
        int result = factor();

        while (currentToken == Token.MULTIPLY || currentToken == Token.DIVIDE) {
            int op = currentToken;
            currentToken = getNextToken();
            int factorValue = factor();

            if (op == Token.MULTIPLY) {
                result *= factorValue;
            } else {
                if (factorValue != 0) {
                    result /= factorValue;
                } else {
                    throw new RuntimeException("Деление на ноль");
                }
            }
        }

        return result;
    }

    private int factor() {
        int result;
        int token = currentToken;

        if (token == Token.LPAREN) {
            currentToken = getNextToken();
            result = expression();
            if (currentToken != Token.RPAREN) {
                throw new RuntimeException("Ожидается ')'");
            }
            currentToken = getNextToken();
        } else if (token == Token.NUMBER) {
            result = Integer.parseInt(tokenValue);
            currentToken = getNextToken();
        } else if (token == Token.IDENTIFIER) {
            result = getVariable(tokenValue);
            currentToken = getNextToken();
        } else {
            throw new RuntimeException("Недопустимый фактор: " + tokenValue);
        }

        return result;
    }

    // Анализ булевого выражения
    private boolean booleanExpression() {
        int left = expression();

        int relop = currentToken;
        if (relop != Token.LESS && relop != Token.GREATER &&
                relop != Token.EQUAL && relop != Token.NOT_EQUAL) {
            throw new RuntimeException("Ожидается оператор сравнения, получено: " + tokenValue);
        }

        currentToken = getNextToken();
        int right = expression();

        switch (relop) {
            case Token.LESS:
                return left < right;
            case Token.GREATER:
                return left > right;
            case Token.EQUAL:
                return left == right;
            case Token.NOT_EQUAL:
                return left != right;
            default:
                return false;
        }
    }

    // Обработка оператора print
    private void processPrint() {
        currentToken = getNextToken();

        while (true) {
            if (currentToken == Token.STRING) {
                System.out.print(tokenValue);
                currentToken = getNextToken();
            } else {
                int value = expression();
                System.out.print(value);
            }

            if (currentToken == Token.COMMA) {
                System.out.print(" ");
                currentToken = getNextToken();
            } else {
                break;
            }
        }

        System.out.println();

        if (currentToken != Token.SEMICOLON) {
            throw new RuntimeException("Ожидается ';' после print");
        }
        currentToken = getNextToken();
    }

    // Обработка оператора scan
    private void processScan() {
        currentToken = getNextToken();

        if (currentToken != Token.IDENTIFIER) {
            throw new RuntimeException("Ожидается идентификатор после scan");
        }

        String varName = tokenValue;
        System.out.print("Введите значение для " + varName + ": ");
        int value = scanner.nextInt();
        setVariable(varName, value);

        currentToken = getNextToken();

        if (currentToken != Token.SEMICOLON) {
            throw new RuntimeException("Ожидается ';' после scan");
        }
        currentToken = getNextToken();
    }

    // Обработка оператора присваивания
    private void processAssign() {
        String varName = tokenValue;
        currentToken = getNextToken();

        if (currentToken != Token.ASSIGN) {
            throw new RuntimeException("Ожидается '='");
        }

        currentToken = getNextToken();
        int value = expression();
        setVariable(varName, value);

        if (currentToken == Token.SEMICOLON) {
            currentToken = getNextToken();
        }
    }

    // Обработка оператора if
    private void processIf() {
        currentToken = getNextToken();
        boolean condition = booleanExpression();

        if (currentToken == Token.LBRACE) {
            currentToken = getNextToken();

            if (condition) {
                mainLoop();

                // Пропускаем блок else если он есть
                if (currentToken == Token.ELSE) {
                    currentToken = getNextToken();
                    if (currentToken == Token.LBRACE) {
                        currentToken = getNextToken();
                        skipBlock();
                    }
                }
            } else {
                skipBlock();

                // Обрабатываем блок else если он есть
                if (currentToken == Token.ELSE) {
                    currentToken = getNextToken();
                    if (currentToken == Token.LBRACE) {
                        currentToken = getNextToken();
                        mainLoop();
                    }
                }
            }
        }
    }

    // Пропуск блока кода
    private void skipBlock() {
        int braceCount = 1;
        while (currentToken != Token.END && braceCount > 0) {
            if (currentToken == Token.LBRACE) braceCount++;
            else if (currentToken == Token.RBRACE) braceCount--;
            currentToken = getNextToken();
        }
    }

    // Обработка цикла for
    private void processFor() {
        currentToken = getNextToken();

        if (currentToken != Token.IDENTIFIER) {
            throw new RuntimeException("Ожидается идентификатор после for");
        }

        String varName = tokenValue;
        currentToken = getNextToken();

        if (currentToken != Token.ASSIGN) {
            throw new RuntimeException("Ожидается '=' в for");
        }

        currentToken = getNextToken();
        int startValue = expression();

        if (currentToken != Token.TO) {
            throw new RuntimeException("Ожидается 'to' в for");
        }

        currentToken = getNextToken();
        int endValue = expression();

        // Сохраняем текущее состояние для начала тела цикла
        int savedPos = pos;
        String savedProgram = program;
        int savedToken = currentToken;

        // Создаем состояние цикла
        ForState forState = new ForState(varName, startValue, endValue, savedPos, savedProgram, savedToken);
        forStack.push(forState);

        // Устанавливаем начальное значение переменной цикла
        setVariable(varName, startValue);

        if (currentToken != Token.LBRACE) {
            throw new RuntimeException("Ожидается '{' после for");
        }

        currentToken = getNextToken();
    }

    // Проверка условия продолжения цикла for
    private boolean shouldContinueForLoop() {
        if (forStack.isEmpty()) return false;

        ForState state = forStack.peek();
        int currentValue = getVariable(state.var);
        return currentValue < state.target;
    }

    // Подготовка к следующей итерации цикла
    private void prepareNextForIteration() {
        if (forStack.isEmpty()) return;

        ForState state = forStack.peek();

        // Увеличиваем переменную цикла
        int currentValue = getVariable(state.var);
        setVariable(state.var, currentValue + 1);

        // Восстанавливаем состояние парсера к началу тела цикла
        pos = state.loopStartPos;
        program = state.loopStartProgram;
        currentToken = state.loopStartToken;
    }

    // Завершение цикла for
    private void endForLoop() {
        if (!forStack.isEmpty()) {
            ForState state = forStack.pop();
            // Восстанавливаем исходное значение переменной
            setVariable(state.var, state.currentValue);
        }
    }

    // Главный цикл интерпретатора
    private void mainLoop() {
        while (currentToken != Token.END && currentToken != Token.RBRACE) {
            switch (currentToken) {
                case Token.PRINT:
                    processPrint();
                    break;

                case Token.SCAN:
                    processScan();
                    break;

                case Token.FOR:
                    // Обрабатываем заголовок for
                    processFor();

                    // Запоминаем размер стека до выполнения тела цикла
                    int stackSizeBefore = forStack.size();

                    // Выполняем тело цикла
                    mainLoop();

                    // Продолжаем цикл, пока условие выполняется
                    while (shouldContinueForLoop() && forStack.size() == stackSizeBefore) {
                        prepareNextForIteration();
                        mainLoop();
                    }

                    // Завершаем цикл
                    if (!forStack.isEmpty() && forStack.size() >= stackSizeBefore) {
                        endForLoop();
                    }
                    break;

                case Token.IF:
                    processIf();
                    break;

                case Token.IDENTIFIER:
                    processAssign();
                    break;

                default:
                    currentToken = getNextToken();
                    break;
            }
        }

        if (currentToken == Token.RBRACE) {
            currentToken = getNextToken();
        }
    }

    // Запуск интерпретатора
    public void interpret() {
        try {
            System.out.println("Начало интерпретации...");
            currentToken = getNextToken();
            mainLoop();
            System.out.println("Интерпретация завершена.");
        } catch (Exception e) {
            System.err.println("Ошибка интерпретации: " + e.getMessage());
            e.printStackTrace();
        }
    }

    // Метод для чтения программы из файла
    public static String readProgramFromFile(String filename) {
        StringBuilder sb = new StringBuilder();
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                sb.append(line).append("\n");
            }
        } catch (IOException e) {
            System.err.println("Ошибка чтения файла: " + e.getMessage());
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        String program = readProgramFromFile("./src/input.txt");
        System.out.println("Загруженная программа:");
        System.out.println(program);
        System.out.println("====================");

        CBASInterpreter interpreter = new CBASInterpreter(program);
        interpreter.interpret();
    }
}