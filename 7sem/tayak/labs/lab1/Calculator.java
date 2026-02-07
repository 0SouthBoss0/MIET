import java.util.ArrayList;
import java.util.Stack;
import java.util.LinkedList;
import java.util.Queue;

public class Calculator {

    private static void saveNumberBuff(ArrayList<CalculatorToken> tokenizedInput, String numberBuffer, boolean addMult) {
        tokenizedInput.add(new DigitToken(Double.valueOf(numberBuffer)));
        if (addMult) {
            tokenizedInput.add(new OperatorToken("*"));
        }
    }

    private static void saveLetterBuff(ArrayList<CalculatorToken> tokenizedInput, String letterBuffer) {
        tokenizedInput.add(new FunctionToken(letterBuffer));
    }

    private static void saveConstants(ArrayList<CalculatorToken> tokenizedInput, String letterBuffer) {
        if (letterBuffer.equals("pi") || letterBuffer.equals("π")) {
            tokenizedInput.add(new DigitToken(Math.PI));
        }
        if (letterBuffer.equals("e")) {
            tokenizedInput.add(new DigitToken(Math.E));
        }
    }

    public static ArrayList<CalculatorToken> tokenize(String expression) throws CalculatorException {
        ArrayList<CalculatorToken> tokenizedInput = new ArrayList<>();
        String[] operators = {"+", "-", "*", "/", "%", "^"};

        // Проверка на пустую строку
        if (expression == null || expression.trim().isEmpty()) {
            throw new CalculatorException("Пустое выражение!");
        }

        StringBuilder numberBuffer = new StringBuilder();
        StringBuilder letterBuffer = new StringBuilder();
        String inputClean = expression.replace(" ", "");

        try {
            for (int i = 0; i < inputClean.length(); i++) {
                char symbol = inputClean.charAt(i);

                if (Character.isDigit(symbol)) {
                    // if symbol is a digit -> send symbol to number buffer
                    numberBuffer.append(symbol);

                } else if (Character.isLetter(symbol)) {
                    // if symbol is a letter -> save number buffer and send symbol to letter buffer
                    if (!numberBuffer.isEmpty()) {
                        saveNumberBuff(tokenizedInput, numberBuffer.toString(), true);
                        numberBuffer = new StringBuilder();
                    }
                    letterBuffer.append(symbol);

                } else if (symbol == '!') {
                    // checking for postfix factorial function
                    if (!numberBuffer.isEmpty()) {
                        saveNumberBuff(tokenizedInput, numberBuffer.toString(), false);
                        numberBuffer = new StringBuilder();
                    }
                    if (!letterBuffer.isEmpty()) {
                        saveLetterBuff(tokenizedInput, letterBuffer.toString());
                        letterBuffer = new StringBuilder();
                    }
                    tokenizedInput.add(new FunctionToken(String.valueOf(symbol)));

                } else if (contains(operators, String.valueOf(symbol))) {
                    // if symbol is an operator -> save number buffer and check for constants in letter buffer
                    if (!numberBuffer.isEmpty()) {
                        saveNumberBuff(tokenizedInput, numberBuffer.toString(), false);
                        numberBuffer = new StringBuilder();
                    }
                    if (!letterBuffer.isEmpty()) {
                        saveConstants(tokenizedInput, letterBuffer.toString());
                        letterBuffer = new StringBuilder();
                    }

                    // Проверка на множественные операторы (кроме унарного минуса в начале)
                    if (i > 0 && contains(operators, String.valueOf(inputClean.charAt(i - 1))) &&
                            !String.valueOf(inputClean.charAt(i - 1)).equals("(") && symbol != '-') {
                        throw new CalculatorException("Некорректная последовательность операторов!");
                    }
                    if (symbol == '-' && i > 0 && inputClean.charAt(i - 1) == '-') {
                        throw new CalculatorException("Некорректная последовательность операторов!");
                    }
                    // checking if minus is unary minus -> if it is a first char or previous token is operator or OpenBracket
                    if (symbol == '-' && (i == 0 || contains(operators, String.valueOf(inputClean.charAt(i - 1))) || inputClean.charAt(i - 1) == '(')) {
                        symbol = '~';
                    }
                    tokenizedInput.add(new OperatorToken(String.valueOf(symbol)));

                } else if (symbol == '(') {
                    // if symbol is a OpenBracket -> save letter buffer and number buffer
                    // Проверка на неявное умножение: число( или )( или функция(
                    if (!tokenizedInput.isEmpty()) {
                        CalculatorToken lastToken = tokenizedInput.getLast();
                        if (lastToken instanceof DigitToken ||
                                lastToken instanceof CloseBracketToken ||
                                (lastToken instanceof FunctionToken && !lastToken.get_t_value().equals("!"))) {
                            tokenizedInput.add(new OperatorToken("*"));
                        }
                    }

                    if (!letterBuffer.isEmpty()) {
                        saveLetterBuff(tokenizedInput, letterBuffer.toString());
                        letterBuffer = new StringBuilder();
                    } else if (!numberBuffer.isEmpty()) {
                        saveNumberBuff(tokenizedInput, numberBuffer.toString(), true);
                        numberBuffer = new StringBuilder();
                    }

                    // Проверка на некорректные последовательности типа "(,"
                    if (i > 0 && inputClean.charAt(i - 1) == ',') {
                        throw new CalculatorException("Некорректное использование запятой перед открывающей скобкой!");
                    }

                    tokenizedInput.add(new OpenBracketToken(String.valueOf(symbol)));

                } else if (symbol == ')') {
                    // if symbol is a CloseBracket -> save number buffer and check for constants in letter buffer
                    if (!numberBuffer.isEmpty()) {
                        saveNumberBuff(tokenizedInput, numberBuffer.toString(), false);
                        numberBuffer = new StringBuilder();
                    }
                    if (!letterBuffer.isEmpty()) {
                        saveConstants(tokenizedInput, letterBuffer.toString());
                        letterBuffer = new StringBuilder();
                    }

                    // Проверка на пустые скобки ()
                    if (!tokenizedInput.isEmpty() && tokenizedInput.getLast() instanceof OpenBracketToken) {
                        throw new CalculatorException("Пустые скобки!");
                    }

                    tokenizedInput.add(new CloseBracketToken(String.valueOf(symbol)));

                    // Проверка на неявное умножение: )( или )число
                    if (i < inputClean.length() - 1 && (Character.isDigit(inputClean.charAt(i + 1)) ||
                            inputClean.charAt(i + 1) == '(' ||
                            Character.isLetter(inputClean.charAt(i + 1)))) {
                        tokenizedInput.add(new OperatorToken("*"));
                    }

                } else if (symbol == '.') {
                    // if symbol is a decimal point -> send symbol to number buffer
                    // Проверка на множественные точки в числе
                    if (numberBuffer.toString().contains(".")) {
                        throw new CalculatorException("Некорректное число!");
                    }
                    numberBuffer.append('.');

                } else if (symbol == ',') {
                    // if symbol is a delimiter -> save number buffer and check for constants in letter buffer
                    if (!numberBuffer.isEmpty()) {
                        saveNumberBuff(tokenizedInput, numberBuffer.toString(), false);
                        numberBuffer = new StringBuilder();
                    }
                    if (!letterBuffer.isEmpty()) {
                        saveConstants(tokenizedInput, letterBuffer.toString());
                        letterBuffer = new StringBuilder();
                    }

                    // Проверка на некорректное использование запятой
                    if (i == 0 || i == inputClean.length() - 1 ||
                            contains(operators, String.valueOf(inputClean.charAt(i - 1))) ||
                            inputClean.charAt(i - 1) == '(' ||
                            contains(operators, String.valueOf(inputClean.charAt(i + 1))) ||
                            inputClean.charAt(i + 1) == ')' || inputClean.charAt(i + 1) == ',') {
                        throw new CalculatorException("Некорректное использование запятой!");
                    }

                    tokenizedInput.add(new SeparatorToken(String.valueOf(symbol)));
                } else {
                    throw new CalculatorException("Некорректный символ в выражении - " + symbol);
                }
            }

            // after-saving number buffer
            if (!numberBuffer.isEmpty()) {
                saveNumberBuff(tokenizedInput, numberBuffer.toString(), false);
            }
            // after-saving letter buffer
            if (!letterBuffer.isEmpty()) {
                saveConstants(tokenizedInput, letterBuffer.toString());
            }

            // Проверка на некорректное окончание выражения
            if (!tokenizedInput.isEmpty() &&
                    (tokenizedInput.getLast() instanceof OperatorToken || tokenizedInput.getLast() instanceof SeparatorToken)) {
                throw new CalculatorException("Выражение не может заканчиваться оператором или разделителем!");
            }

        } catch (CalculatorException e) {
            throw new CalculatorException("Ошибка во время токенизации: " + e.getMessage());
        }
        return tokenizedInput;
    }


    public static Queue<CalculatorToken> sortMachineAlgo(ArrayList<CalculatorToken> parsedTokens) throws CalculatorException {
        /**
         * Realization of Shunting yard algorithm
         * Taken from https://en.wikipedia.org/wiki/Shunting_yard_algorithm (without separators)
         * and https://habr.com/ru/articles/777368/ (with separators)
         * @param parsedTokens CalculatorTokens of inputted expression
         * @return queue with CalculatorTokens in a postfix notation string, also known as reverse Polish notation (RPN)
         */
        Queue<CalculatorToken> queue = new LinkedList<>();
        Stack<CalculatorToken> stack = new Stack<>();

        // Счетчик скобок для проверки сбалансированности
        int bracketCount = 0;

        for (CalculatorToken token : parsedTokens) {
            if (token instanceof OpenBracketToken) {
                bracketCount++;
            } else if (token instanceof CloseBracketToken) {
                bracketCount--;
                if (bracketCount < 0) {
                    throw new CalculatorException("В выражении не согласованы скобки!");
                }
            }
        }

        if (bracketCount != 0) {
            throw new CalculatorException("В выражении не согласованы скобки!");
        }

        for (CalculatorToken token : parsedTokens) {
            switch (token) {
                case DigitToken dt:
                    // token is a digit -> put it into the output queue
                    queue.add(dt);
                    break;

                case FunctionToken ft:
                    // token is a function -> push it onto the operator stack
                    if (ft.t_value.equals("!")) {
                        // handling postfix factorial function
                        queue.add(ft);
                    } else {
                        stack.push(ft);
                    }
                    break;

                case OpenBracketToken obt:
                    // token in an OpenBracket -> push it onto the operator stack
                    stack.push(obt);
                    break;

                case CloseBracketToken cbt:
                    // token in an CloseBracket
                    try {
                        // while the operator at the top of the operator stack is not a OpenBracket
                        while (!(stack.peek() instanceof OpenBracketToken)) {
                            // pop the operator from the operator stack into the output queue
                            queue.add(stack.pop());
                        }
                        // pop the OpenBracket from the operator stack and discard it
                        stack.pop();

                        if (!stack.isEmpty() && stack.peek() instanceof FunctionToken) {
                            // if there is a function token at the top of the operator stack ->
                            // pop the function from the operator stack into the output queue
                            queue.add(stack.pop());
                        }
                    } catch (Exception err) {
                        throw new CalculatorException(
                                "В выражении либо неверно поставлен разделитель, либо не согласованы скобки!");
                    }
                    break;

                case SeparatorToken st:
                    // while the operator at the top of the operator stack is not a OpenBracket
                    try {
                        while (!(stack.peek() instanceof OpenBracketToken)) {
                            // pop the operator from the operator stack into the output queue
                            queue.add(stack.pop());
                        }
                    } catch (Exception err) {
                        throw new CalculatorException(
                                "Проблема с разделителем - вероятно, использована десятичная запятая вместо точки!");
                    }
                    break;

                case OperatorToken ot:
                    // while there is an operator o2 at the top of the operator stack
                    // and o2 has same or greater precedence than o1
                    while (!stack.isEmpty() &&
                            stack.peek() instanceof OperatorToken &&
                            ((OperatorToken) stack.peek()).priority >= ot.priority) {
                        // pop o2 from the operator stack into the output queue
                        queue.add(stack.pop());
                    }
                    // push o1 onto the operator stack
                    stack.push(token);
                    break;
                default:
                    throw new IllegalStateException("Unexpected value: " + token);
            }
        }

        while (!stack.isEmpty()) {
            // while there are tokens on the operator stack
            CalculatorToken temp = stack.pop();
            if (temp instanceof OpenBracketToken || temp instanceof CloseBracketToken) {
                // there are mismatched parentheses
                throw new CalculatorException("В выражении не согласованы скобки");
            } else {
                // pop the operator from the operator stack onto the output queue
                queue.add(temp);
            }
        }
        return queue;
    }

    public static double evaluate(Queue<CalculatorToken> expression) throws CalculatorException {
        /**
         * Function to evaluate expression in Reverse Polish Notation (RPN)
         * Algorithm taken from https://www.geeksforgeeks.org/evaluation-of-postfix-expression/?ysclid=m3a2cblkdp275675497
         * @param expression: queue with CalculatorTokens sorted in RPN
         * @return: value of evaluated expression
         */
        Stack<Double> stack = new Stack<>();

        // Функции с фиксированным количеством аргументов
        java.util.Map<String, Integer> functionArgCount = new java.util.HashMap<>();
        functionArgCount.put("log", 2);
        functionArgCount.put("min", 2);
        functionArgCount.put("max", 2);
        functionArgCount.put("sin", 1);
        functionArgCount.put("cos", 1);
        functionArgCount.put("tan", 1);
        functionArgCount.put("cot", 1);
        functionArgCount.put("sqrt", 1);
        functionArgCount.put("ln", 1);
        functionArgCount.put("fact", 1);
        functionArgCount.put("!", 1);
        functionArgCount.put("~", 1);
        functionArgCount.put("+", 2);
        functionArgCount.put("-", 2);
        functionArgCount.put("*", 2);
        functionArgCount.put("/", 2);
        functionArgCount.put("^", 2);
        functionArgCount.put("%", 2);

        for (CalculatorToken token : expression) {
            if (token instanceof DigitToken) {
                // token is a digit -> push to stack
                stack.push(((DigitToken) token).get_value());
            } else if (token instanceof OperatorToken || token instanceof FunctionToken) {
                String tokenValue;
                if (token instanceof OperatorToken) {
                    tokenValue = ((OperatorToken) token).get_value();
                } else {
                    tokenValue = ((FunctionToken) token).get_value();
                }

                if (functionArgCount.containsKey(tokenValue)) {
                    int argCount = functionArgCount.get(tokenValue);

                    if (stack.size() < argCount) {
                        throw new CalculatorException(
                                "Недостаточно операндов для оператора " + tokenValue + "!");
                    }

                    try {
                        if (argCount == 1) {
                            // Унарные операторы и функции
                            double a = stack.pop();
                            double result = 0;

                            switch (tokenValue) {
                                case "~":
                                    result = -a;
                                    break;
                                case "sin":
                                    result = Math.sin(a);
                                    break;
                                case "cos":
                                    result = Math.cos(a);
                                    break;
                                case "tan":
                                    result = Math.tan(a);
                                    break;
                                case "cot":
                                    result = 1.0 / Math.tan(a);
                                    break;
                                case "sqrt":
                                    if (a < 0) {
                                        throw new CalculatorException("Ошибка: извлечение корня из отрицательного числа!");
                                    }
                                    result = Math.sqrt(a);
                                    break;
                                case "ln":
                                    if (a <= 0) {
                                        throw new CalculatorException("Ошибка: логарифм неположительного числа!");
                                    }
                                    result = Math.log(a);
                                    break;
                                case "fact":
                                case "!":
                                    if (a < 0 || a != Math.floor(a)) {
                                        throw new CalculatorException("Ошибка: факториал определен только для неотрицательных целых чисел!");
                                    }
                                    result = factorial((int) a);
                                    break;
                                default:
                                    throw new CalculatorException("Неизвестная унарная функция: " + tokenValue);
                            }
                            stack.push(result);

                        } else if (argCount == 2) {
                            // Бинарные операторы и функции
                            double a = stack.pop();
                            double b = stack.pop();
                            double result = 0;

                            switch (tokenValue) {
                                case "+":
                                    result = b + a;
                                    break;
                                case "-":
                                    result = b - a;
                                    break;
                                case "*":
                                    result = b * a;
                                    break;
                                case "/":
                                    if (a == 0) {
                                        throw new CalculatorException("Ошибка: деление на ноль!");
                                    }
                                    result = b / a;
                                    break;
                                case "%":
                                    if (a == 0) {
                                        throw new CalculatorException("Ошибка: деление на ноль при взятии остатка!");
                                    }
                                    result = b % a;
                                    break;
                                case "^":
                                    result = Math.pow(b, a);
                                    break;
                                case "log":
                                    if (b <= 0 || b == 1 || a <= 0) {
                                        throw new CalculatorException("Ошибка: некорректные аргументы для логарифма!");
                                    }
                                    result = Math.log(a) / Math.log(b);
                                    break;
                                case "min":
                                    result = Math.min(b, a);
                                    break;
                                case "max":
                                    result = Math.max(b, a);
                                    break;
                                default:
                                    throw new CalculatorException("Неизвестный бинарный оператор: " + tokenValue);
                            }
                            stack.push(result);
                        }
                    } catch (CalculatorException e) {
                        throw e;
                    } catch (Exception err) {
                        throw new CalculatorException("Ошибка во время вычисления " + tokenValue + "!");
                    }
                } else {
                    throw new CalculatorException("Неизвестный оператор или функция: " + tokenValue);
                }
            }
        }

        if (stack.size() != 1) {
            throw new CalculatorException("Некорректное выражение!");
        }

        return stack.pop();
    }

    // Вспомогательная функция для вычисления факториала
    private static double factorial(int n) {
        if (n == 0 || n == 1) {
            return 1;
        }
        double result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

    // Вспомогательные методы
    private static boolean contains(String[] array, String value) {
        for (String item : array) {
            if (item.equals(value)) {
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) throws CalculatorException {
        ArrayList<CalculatorToken> t = tokenize("");
        Queue<CalculatorToken> rpn = sortMachineAlgo(t);
        System.out.println(evaluate(rpn));
    }
}