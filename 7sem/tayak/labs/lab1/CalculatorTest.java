import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.*;

import static org.junit.jupiter.api.Assertions.*;

public class CalculatorTest {

    @BeforeEach
    public void setUp() {
    }

    @Test
    public void testInputTokenizeSum2() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("+"),
                new DigitToken(3.0)
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("2+3");
        assertEquals(expected, actual);
    }

    @Test
    public void testInputTokenizeSum3() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("+"),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new DigitToken(4.0)
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("2+3+4");
        assertEquals(expected, actual);
    }

    @Test
    public void testInputTokenizeUnaryMinus() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new OperatorToken("~"),
                new DigitToken(2.0),
                new OperatorToken("-"),
                new DigitToken(4.0),
                new OperatorToken("+"),
                new OpenBracketToken("("),
                new OperatorToken("~"),
                new DigitToken(3.0),
                new CloseBracketToken(")"),
                new OperatorToken("-"),
                new OpenBracketToken("("),
                new OperatorToken("~"),
                new DigitToken(5.0),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("-2-4+(-3)-(-5)");
        assertEquals(expected, actual);
    }

    @Test
    public void testInputTokenizeWithBrackets() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("+"),
                new OpenBracketToken("("),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new OpenBracketToken("("),
                new DigitToken(4.0),
                new OperatorToken("+"),
                new DigitToken(5.0),
                new CloseBracketToken(")"),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("2+(3+(4+5))");
        assertEquals(expected, actual);
    }

    @Test
    public void testInputTokenizeWithFunctionsAndConstants() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(0.1),
                new OperatorToken("+"),
                new FunctionToken("sin"),
                new OpenBracketToken("("),
                new DigitToken(Math.PI),
                new CloseBracketToken(")"),
                new OperatorToken("-"),
                new FunctionToken("log"),
                new OpenBracketToken("("),
                new DigitToken(2.0),
                new SeparatorToken(","),
                new DigitToken(64.0),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("0.1+sin(pi)-log(2, 64)");
        assertEquals(expected, actual);
    }

    @Test
    public void testInputTokenizeWithBracketsAndIgnoredMult() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("+"),
                new OpenBracketToken("("),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new DigitToken(4.0),
                new OperatorToken("*"),
                new OpenBracketToken("("),
                new DigitToken(5.0),
                new OperatorToken("+"),
                new DigitToken(6.0),
                new CloseBracketToken(")"),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("2+(3+4(5+6))");
        assertEquals(expected, actual);
    }

    @Test
    public void testComplexExpressionWithAllOperations() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new OpenBracketToken("("),
                new DigitToken(2.0),
                new OperatorToken("*"),
                new OpenBracketToken("("),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new DigitToken(4.0),
                new CloseBracketToken(")"),
                new OperatorToken("-"),
                new DigitToken(5.0),
                new OperatorToken("/"),
                new DigitToken(2.0),
                new CloseBracketToken(")"),
                new OperatorToken("^"),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new FunctionToken("sqrt"),
                new OpenBracketToken("("),
                new DigitToken(16.0),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("(2*(3+4)-5/2)^3+sqrt(16)");
        assertEquals(expected, actual);
    }

    @Test
    public void testNestedFunctions() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new FunctionToken("sin"),
                new OpenBracketToken("("),
                new FunctionToken("cos"),
                new OpenBracketToken("("),
                new FunctionToken("tan"),
                new OpenBracketToken("("),
                new DigitToken(45.0),
                new CloseBracketToken(")"),
                new CloseBracketToken(")"),
                new CloseBracketToken(")"),
                new OperatorToken("*"),
                new FunctionToken("log"),
                new OpenBracketToken("("),
                new DigitToken(10.0),
                new SeparatorToken(","),
                new DigitToken(100.0),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("sin(cos(tan(45)))*log(10, 100)");
        assertEquals(expected, actual);
    }


    @Test
    public void testImplicitMultiplicationComplex() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("*"),
                new OpenBracketToken("("),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new DigitToken(4.0),
                new CloseBracketToken(")"),
                new OperatorToken("*"),
                new FunctionToken("sin"),
                new OpenBracketToken("("),
                new DigitToken(Math.PI),
                new CloseBracketToken(")"),
                new OperatorToken("*"),
                new OpenBracketToken("("),
                new DigitToken(5.0),
                new OperatorToken("-"),
                new DigitToken(1.0),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("2(3+4)sin(pi)(5-1)");
        assertEquals(expected, actual);
    }


    @Test
    public void testComplexExpressionWithSpaces() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new FunctionToken("max"),
                new OpenBracketToken("("),
                new DigitToken(2.0),
                new SeparatorToken(","),
                new FunctionToken("min"),
                new OpenBracketToken("("),
                new DigitToken(3.0),
                new SeparatorToken(","),
                new DigitToken(5.0),
                new CloseBracketToken(")"),
                new SeparatorToken(","),
                new DigitToken(7.0),
                new CloseBracketToken(")"),
                new OperatorToken("*"),
                new OpenBracketToken("("),
                new DigitToken(1.0),
                new OperatorToken("+"),
                new DigitToken(2.0),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("max(2, min(3, 5), 7) * (1 + 2)");
        assertEquals(expected, actual);
    }

    @Test
    public void testDecimalNumbersAndMultipleSeparators() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(0.123),
                new OperatorToken("+"),
                new DigitToken(45.678),
                new OperatorToken("*"),
                new FunctionToken("pow"),
                new OpenBracketToken("("),
                new DigitToken(2.0),
                new SeparatorToken(","),
                new DigitToken(3.5),
                new SeparatorToken(","),
                new DigitToken(1.2),
                new CloseBracketToken(")"),
                new OperatorToken("-"),
                new DigitToken(999.999)
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("0.123 + 45.678 * pow(2, 3.5, 1.2) - 999.999");
        assertEquals(expected, actual);
    }

    @Test
    public void testMixedUnaryAndBinaryMinus() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(10.0),
                new OperatorToken("-"),
                new DigitToken(5.0),
                new OperatorToken("-"),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new OperatorToken("~"),
                new OpenBracketToken("("),
                new DigitToken(2.0),
                new OperatorToken("-"),
                new DigitToken(1.0),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("10 - 5 - 3 + -(2 - 1)");
        assertEquals(expected, actual);
    }

    @Test
    public void testVeryLongExpression() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(1.0),
                new OperatorToken("+"),
                new DigitToken(2.0),
                new OperatorToken("*"),
                new DigitToken(3.0),
                new OperatorToken("-"),
                new DigitToken(4.0),
                new OperatorToken("/"),
                new DigitToken(5.0),
                new OperatorToken("+"),
                new FunctionToken("sin"),
                new OpenBracketToken("("),
                new DigitToken(Math.PI),
                new OperatorToken("/"),
                new DigitToken(2.0),
                new CloseBracketToken(")"),
                new OperatorToken("*"),
                new DigitToken(6.0),
                new OperatorToken("^"),
                new DigitToken(2.0),
                new OperatorToken("-"),
                new FunctionToken("log"),
                new OpenBracketToken("("),
                new DigitToken(10.0),
                new SeparatorToken(","),
                new DigitToken(100.0),
                new CloseBracketToken(")"),
                new OperatorToken("+"),
                new DigitToken(7.0)
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("1+2*3-4/5+sin(pi/2)*6^2-log(10,100)+7");
        assertEquals(expected, actual);
    }

    @Test
    public void testExpressionWithAllTokenTypes() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new OpenBracketToken("("),
                new DigitToken(1.0),
                new OperatorToken("+"),
                new DigitToken(2.0),
                new CloseBracketToken(")"),
                new OperatorToken("*"),
                new FunctionToken("cos"),
                new OpenBracketToken("("),
                new DigitToken(0.0),
                new CloseBracketToken(")"),
                new OperatorToken("-"),
                new FunctionToken("pow"),
                new OpenBracketToken("("),
                new DigitToken(2.0),
                new SeparatorToken(","),
                new DigitToken(3.0),
                new SeparatorToken(","),
                new DigitToken(4.0),
                new CloseBracketToken(")"),
                new OperatorToken("+"),
                new DigitToken(Math.E),
                new OperatorToken("/"),
                new DigitToken(Math.PI)
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("(1+2)*cos(0)-pow(2,3,4)+e/pi");
        assertEquals(expected, actual);
    }

    @Test
    public void testDeeplyNestedBrackets() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new FunctionToken("sin"),
                new OpenBracketToken("("),
                new OpenBracketToken("("),
                new OpenBracketToken("("),
                new OpenBracketToken("("),
                new DigitToken(1.0),
                new OperatorToken("+"),
                new DigitToken(1.0),
                new CloseBracketToken(")"),
                new CloseBracketToken(")"),
                new CloseBracketToken(")"),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("sin((((1+1))))");
        assertEquals(expected, actual);
    }

    @Test
    public void testComplexPowerOperations() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("^"),
                new DigitToken(3.0),
                new OperatorToken("^"),
                new DigitToken(2.0),
                new OperatorToken("*"),
                new OpenBracketToken("("),
                new DigitToken(4.0),
                new OperatorToken("^"),
                new OperatorToken("~"),
                new DigitToken(1.0),
                new CloseBracketToken(")")
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("2^3^2*(4^-1)");
        assertEquals(expected, actual);
    }

    @Test
    public void testExpressionWithWhitespaceVariations() throws CalculatorException {
        ArrayList<CalculatorToken> expected = new ArrayList<>(Arrays.asList(
                new DigitToken(1.0),
                new OperatorToken("+"),
                new DigitToken(2.0),
                new OperatorToken("*"),
                new OpenBracketToken("("),
                new DigitToken(3.0),
                new OperatorToken("-"),
                new DigitToken(4.0),
                new CloseBracketToken(")"),
                new OperatorToken("/"),
                new DigitToken(5.0)
        ));
        ArrayList<CalculatorToken> actual = Calculator.tokenize("  1 + 2 * ( 3 - 4 ) / 5  ");
        assertEquals(expected, actual);
    }


    @Test
    public void testSortMachineAlgoSum2() throws CalculatorException {
        ArrayList<CalculatorToken> input = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("+"),
                new DigitToken(3.0)
        ));
        Queue<CalculatorToken> expected = new LinkedList<>(Arrays.asList(
                new DigitToken(2.0),
                new DigitToken(3.0),
                new OperatorToken("+"))
        );

        Queue<CalculatorToken> actual = Calculator.sortMachineAlgo(input);
        assertEquals(expected, actual);
    }

    @Test
    public void testSortMachineAlgoSumAndMult() throws CalculatorException {
        ArrayList<CalculatorToken> input = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("+"),
                new DigitToken(3.0),
                new OperatorToken("*"),
                new DigitToken(4.0)
        ));
        Queue<CalculatorToken> expected = new LinkedList<>(Arrays.asList(
                new DigitToken(2.0),
                new DigitToken(3.0),
                new DigitToken(4.0),
                new OperatorToken("*"),
                new OperatorToken("+"))
        );

        Queue<CalculatorToken> actual = Calculator.sortMachineAlgo(input);
        assertEquals(expected, actual);
    }

    @Test
    public void testSortMachineAlgoSum3() throws CalculatorException {
        ArrayList<CalculatorToken> input = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("+"),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new DigitToken(4.0)
        ));
        Queue<CalculatorToken> expected = new LinkedList<>(Arrays.asList(
                new DigitToken(2.0),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new DigitToken(4.0),
                new OperatorToken("+"))
        );

        Queue<CalculatorToken> actual = Calculator.sortMachineAlgo(input);
        assertEquals(expected, actual);
    }

    @Test
    public void testSortMachineAlgoUnaryMinus() throws CalculatorException {
        ArrayList<CalculatorToken> input = new ArrayList<>(Arrays.asList(
                new OperatorToken("~"),
                new DigitToken(2.0),
                new OperatorToken("-"),
                new DigitToken(4.0),
                new OperatorToken("+"),
                new OpenBracketToken("("),
                new OperatorToken("~"),
                new DigitToken(3.0),
                new CloseBracketToken(")"),
                new OperatorToken("-"),
                new OpenBracketToken("("),
                new OperatorToken("~"),
                new DigitToken(5.0),
                new CloseBracketToken(")")
        ));
        Queue<CalculatorToken> expected = new LinkedList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("~"),
                new DigitToken(4.0),
                new OperatorToken("-"),
                new DigitToken(3.0),
                new OperatorToken("~"),
                new OperatorToken("+"),
                new DigitToken(5.0),
                new OperatorToken("~"),
                new OperatorToken("-"))
        );

        Queue<CalculatorToken> actual = Calculator.sortMachineAlgo(input);
        assertEquals(expected, actual);
    }

    @Test
    public void testSortMachineAlgoWithFunctionsAndConstants() throws CalculatorException {
        ArrayList<CalculatorToken> input = new ArrayList<>(Arrays.asList(
                new DigitToken(0.1),
                new OperatorToken("+"),
                new FunctionToken("sin"),
                new OpenBracketToken("("),
                new DigitToken(Math.PI),
                new CloseBracketToken(")"),
                new OperatorToken("-"),
                new FunctionToken("log"),
                new OpenBracketToken("("),
                new DigitToken(2.0),
                new SeparatorToken(","),
                new DigitToken(64.0),
                new CloseBracketToken(")")
        ));
        Queue<CalculatorToken> expected = new LinkedList<>(Arrays.asList(
                new DigitToken(0.1),
                new DigitToken(Math.PI),
                new FunctionToken("sin"),
                new OperatorToken("+"),
                new DigitToken(2.0),
                new DigitToken(64.0),
                new FunctionToken("log"),
                new OperatorToken("-"))
        );

        Queue<CalculatorToken> actual = Calculator.sortMachineAlgo(input);
        assertEquals(expected, actual);
    }

    @Test
    public void testSortMachineAlgoWithBracketsAndIgnoredMult() throws CalculatorException {
        ArrayList<CalculatorToken> input = new ArrayList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("+"),
                new OpenBracketToken("("),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new DigitToken(4.0),
                new OperatorToken("*"),
                new OpenBracketToken("("),
                new DigitToken(5.0),
                new OperatorToken("+"),
                new DigitToken(6.0),
                new CloseBracketToken(")"),
                new CloseBracketToken(")")
        ));
        Queue<CalculatorToken> expected = new LinkedList<>(Arrays.asList(
                new DigitToken(2.0),
                new DigitToken(3.0),
                new DigitToken(4.0),
                new DigitToken(5.0),
                new DigitToken(6.0),
                new OperatorToken("+"),
                new OperatorToken("*"),
                new OperatorToken("+"),
                new OperatorToken("+"))
        );

        Queue<CalculatorToken> actual = Calculator.sortMachineAlgo(input);
        assertEquals(expected, actual);
    }

    @Test
    public void testEvaluateSum2() throws CalculatorException {
        Queue<CalculatorToken> input = new LinkedList<>(Arrays.asList(
                new DigitToken(2.0),
                new DigitToken(3.0),
                new OperatorToken("+")
        ));
        double expected = 5.0;
        double actual = Calculator.evaluate(input);
        assertEquals(expected, actual, 0.0001);
    }

    @Test
    public void testEvaluateSum3() throws CalculatorException {
        Queue<CalculatorToken> input = new LinkedList<>(Arrays.asList(
                new DigitToken(2.0),
                new DigitToken(3.0),
                new OperatorToken("+"),
                new DigitToken(4.0),
                new OperatorToken("+")
        ));
        double expected = 9.0;
        double actual = Calculator.evaluate(input);
        assertEquals(expected, actual, 0.0001);
    }

    @Test
    public void testEvaluateUnaryMinus() throws CalculatorException {
        Queue<CalculatorToken> input = new LinkedList<>(Arrays.asList(
                new DigitToken(2.0),
                new OperatorToken("~"),
                new DigitToken(4.0),
                new OperatorToken("-"),
                new DigitToken(3.0),
                new OperatorToken("~"),
                new OperatorToken("+"),
                new DigitToken(5.0),
                new OperatorToken("~"),
                new OperatorToken("-")
        ));
        double expected = -4.0;
        double actual = Calculator.evaluate(input);
        assertEquals(expected, actual, 0.0001);
    }

    @Test
    public void testEvaluateWithFunctionsAndConstants() throws CalculatorException {
        Queue<CalculatorToken> input = new LinkedList<>(Arrays.asList(
                new DigitToken(0.1),
                new DigitToken(Math.PI),
                new FunctionToken("sin"),
                new OperatorToken("+"),
                new DigitToken(2.0),
                new DigitToken(64.0),
                new FunctionToken("log"),
                new OperatorToken("-")
        ));
        double expected = -5.9;
        double actual = Calculator.evaluate(input);
        assertEquals(expected, actual, 0.0001);
    }

    @Test
    public void testEvaluateWithBracketsAndIgnoredMult() throws CalculatorException {
        Queue<CalculatorToken> input = new LinkedList<>(Arrays.asList(
                new DigitToken(2.0),
                new DigitToken(3.0),
                new DigitToken(4.0),
                new DigitToken(5.0),
                new DigitToken(6.0),
                new OperatorToken("+"),
                new OperatorToken("*"),
                new OperatorToken("+"),
                new OperatorToken("+")
        ));
        double expected = 49.0;
        double actual = Calculator.evaluate(input);
        assertEquals(expected, actual, 0.0001);
    }


    @Test
    public void testTotal() throws CalculatorException {
        Map<String, Double> expressions = new LinkedHashMap<>();

        // Original tests
        expressions.put("2 + 3", 5.0);
        expressions.put("10 - 4", 6.0);
        expressions.put("3 * 5", 15.0);
        expressions.put("20 / 4", 5.0);
        expressions.put("2 + 3 * 4", 14.0);
        expressions.put("(2 + 3) * 4", 20.0);
        expressions.put("10 / 3", 3.3333);
        expressions.put("2.5 + 3.7", 6.2);
        expressions.put("-5 + 10", 5.0);
        expressions.put("2 ^ 3", 8.0);

        // One operation expressions
        expressions.put("3-2", 1.0);
        expressions.put("2-3", -1.0);
        expressions.put("2*3", 6.0);
        expressions.put("4/2", 2.0);
        expressions.put("3*3", 9.0);
        expressions.put("4%3", 1.0);
        expressions.put("-1-3", -4.0);
        expressions.put("(0.9)π", 2.827433388230814);

        // Many operation expressions
        expressions.put("2+3+4", 9.0);
        expressions.put("3-2+5", 6.0);
        expressions.put("3-(2+5)", -4.0);
        expressions.put("(2-3)+(3-4)", -2.0);
        expressions.put("4*(2+3)", 20.0);
        expressions.put("4(2+3)", 20.0);
        expressions.put("-4(-2+3)", -4.0);
        expressions.put("4(-2-(-3))", 4.0);
        expressions.put("2+2*2", 6.0);

        // Long expressions
        expressions.put("15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))", -30.072164948453608);

        // Trigonometric expressions
        expressions.put("(sin(2pi * (3 + (4 / (5 - 2)))) ^ 2) / (1 + (sin(pi / 4)) ^ 3)", 0.5540970937771961);

        // Function expressions
        expressions.put("fact(3)", 6.0);
        expressions.put("3!", 6.0);
        expressions.put("min(2, 5)", 2.0);
        expressions.put("max(-2, 5)", 5.0);
        expressions.put("log(2, 64)", 6.0);
        expressions.put("ln(e)", 1.0);

        // Basic arithmetic variations
        expressions.put("0+0", 0.0);
        expressions.put("0-5", -5.0);
        expressions.put("5-0", 5.0);
        expressions.put("0*5", 0.0);
        expressions.put("5*0", 0.0);
        expressions.put("0/5", 0.0);
        expressions.put("1/1", 1.0);
        expressions.put("10/2", 5.0);
        expressions.put("2^0", 1.0);
        expressions.put("2^1", 2.0);
        expressions.put("0^5", 0.0);
        expressions.put("5%2", 1.0);
        expressions.put("5%5", 0.0);

        // Negative numbers operations
        expressions.put("-5+3", -2.0);
        expressions.put("-5-3", -8.0);
        expressions.put("-5*-3", 15.0);
        expressions.put("-5*3", -15.0);
        expressions.put("-10/2", -5.0);
        expressions.put("-10/-2", 5.0);
        expressions.put("(-2)^3", -8.0);
        expressions.put("(-2)^4", 16.0);

        // Decimal operations
        expressions.put("0.5+0.5", 1.0);
        expressions.put("1.5-0.5", 1.0);
        expressions.put("0.5*4", 2.0);
        expressions.put("1.5/0.5", 3.0);
        expressions.put("0.1+0.2", 0.3);
        expressions.put("2.5^2", 6.25);
        expressions.put("0.25*0.25", 0.0625);

        // Order of operations
        expressions.put("10-4/2", 8.0);
        expressions.put("(10-4)/2", 3.0);
        expressions.put("2^3*4", 32.0);
        expressions.put("2^(3*4)", 4096.0);
        expressions.put("4+3*2^2", 16.0);
        expressions.put("4+3*(2^2)", 16.0);
        expressions.put("100/10^2", 1.0);
        expressions.put("(100/10)^2", 100.0);
        expressions.put("2+3*4-5/1", 9.0);
        expressions.put("(2+3)*(4-5)/1", -5.0);

        // Parentheses combinations
        expressions.put("((2+3))", 5.0);
        expressions.put("(((2+3)*4))", 20.0);
        expressions.put("(2+(3*4))", 14.0);
        expressions.put("((2+3)*(4-1))", 15.0);
        expressions.put("(2*(3+(4*5)))", 46.0);
        expressions.put("((((5))))", 5.0);
        expressions.put("(1+((2*3)+4))", 11.0);
        expressions.put("((1+2)*(3+4)*(5+6))", 231.0);

        // Implicit multiplication
        expressions.put("2(3+4)", 14.0);
        expressions.put("(2+3)4", 20.0);
        expressions.put("3(2)", 6.0);
        expressions.put("(3)(4)", 12.0);
        expressions.put("2(3+4)5", 70.0);
        expressions.put("-2(3+4)", -14.0);
        expressions.put("2(-3+4)", 2.0);
        expressions.put("0.5(10)", 5.0);
        expressions.put("2π", 6.283185307179586);
        expressions.put("2(3+4)(5+6)", 154.0);

        // Trigonometric functions basic
        expressions.put("sin(0)", 0.0);
        expressions.put("sin(pi/2)", 1.0);
        expressions.put("sin(pi)", 0.0);
        expressions.put("cos(0)", 1.0);
        expressions.put("cos(pi/2)", 0.0);
        expressions.put("cos(pi)", -1.0);
        expressions.put("tan(0)", 0.0);
        expressions.put("tan(pi/4)", 1.0);

        // Advanced trigonometric
        expressions.put("sin(pi/6)", 0.5);
        expressions.put("cos(pi/3)", 0.5);
        expressions.put("tan(pi/3)", 1.7320508075688767);
        expressions.put("sin(pi/4)^2", 0.5);
        expressions.put("sin(pi/6)+cos(pi/3)", 1.0);
        expressions.put("2*sin(pi/4)*cos(pi/4)", 1.0);
        expressions.put("sin(pi/2)+cos(pi/2)", 1.0);
        expressions.put("tan(pi/4)+tan(pi/4)", 2.0);

        // Logarithmic functions
        expressions.put("log(10, 100)", 2.0);
        expressions.put("log(2, 8)", 3.0);
        expressions.put("log(5, 25)", 2.0);
        expressions.put("ln(1)", 0.0);
        expressions.put("ln(e^2)", 2.0);
        expressions.put("log(10, 1000)", 3.0);
        expressions.put("log(2, 1)", 0.0);
        expressions.put("ln(e^10)", 10.0);
        expressions.put("log(0.5, 2)", -1.0);

        // Factorial and combinations
        expressions.put("fact(0)", 1.0);
        expressions.put("fact(1)", 1.0);
        expressions.put("fact(5)", 120.0);
        expressions.put("0!", 1.0);
        expressions.put("1!", 1.0);
        expressions.put("5!", 120.0);
        expressions.put("fact(2)+fact(3)", 8.0);
        expressions.put("2!*3!", 12.0);
        expressions.put("fact(4)/fact(2)", 12.0);

        // Min/max functions
        expressions.put("min(1, 2)", 1.0);
        expressions.put("min(-5, 5)", -5.0);
        expressions.put("min(0, 0)", 0.0);
        expressions.put("min(2.5, 3.7)", 2.5);
        expressions.put("max(1, 2)", 2.0);
        expressions.put("max(-5, 5)", 5.0);
        expressions.put("max(0, 0)", 0.0);
        expressions.put("max(2.5, 3.7)", 3.7);
        expressions.put("min(1, min(2, 3))", 1.0);
        expressions.put("max(1, max(2, 3))", 3.0);
        expressions.put("min(max(1,5), 10)", 5.0);

        // Constants usage
        expressions.put("π", 3.141592653589793);
        expressions.put("e", 2.718281828459045);
        expressions.put("π/2", 1.5707963267948966);
        expressions.put("e^1", 2.718281828459045);
        expressions.put("π+e", 5.859874482048838);
        expressions.put("2e", 5.43656365691809);
        expressions.put("π*π", 9.869604401089358);

        // Complex expressions mixing functions
        expressions.put("sin(π/2)+cos(0)", 2.0);
        expressions.put("fact(3)+log(2,8)", 9.0);
        expressions.put("min(5,max(2,10))", 5.0);
        expressions.put("(sin(π/2))^2+(cos(π/2))^2", 1.0);

        // Edge cases and error prevention
        expressions.put("1+2+3+4+5", 15.0);
        expressions.put("1-2-3-4", -8.0);
        expressions.put("2*2*2*2", 16.0);
        expressions.put("100/2/2/5", 5.0);
        expressions.put("2^2^2", 16.0);
        expressions.put("1+-1", 0.0);
        expressions.put("-(-5)", 5.0);

        // Square roots and powers
        expressions.put("sqrt(4)", 2.0);
        expressions.put("sqrt(9)", 3.0);
        expressions.put("sqrt(2)", 1.4142135623730951);
        expressions.put("sqrt(25)", 5.0);
        expressions.put("sqrt(0)", 0.0);
        expressions.put("sqrt(1)", 1.0);
        expressions.put("4^(1/2)", 2.0);
        expressions.put("8^(1/3)", 2.0);
        expressions.put("sqrt(sqrt(16))", 2.0);
        expressions.put("(sqrt(4))^2", 4.0);

        // Modulo calculations
        expressions.put("17 % 5", 2.0);
        expressions.put("100 + 7%4", 103.0);
        expressions.put("50 * 3%2", 50.0);
        expressions.put("10%3 + 20%6", 3.0);

        // Mixed complex expressions
        expressions.put("2+3*4-5/1+2^3", 17.0);
        expressions.put("(2+3)*(4-1)+10/2", 20.0);
        expressions.put("sin(π/2)*cos(0)+fact(3)", 7.0);
        expressions.put("min(5,10)+max(2,8)*2", 21.0);
        expressions.put("(2+3)*(4-1)/(5-2)", 5.0);
        expressions.put("2^(3+1)-sqrt(16)*2", 8.0);
        expressions.put("fact(4)/2+log(10,100)", 14.0);

        for (Map.Entry<String, Double> entry : expressions.entrySet()) {
            String expression = entry.getKey();
            Double expectedValue = entry.getValue();

            ArrayList<CalculatorToken> t = Calculator.tokenize(expression);
            Queue<CalculatorToken> rpn = Calculator.sortMachineAlgo(t);
            assertEquals(expectedValue, Calculator.evaluate(rpn), 0.0001);
        }
    }

    @Test
    public void testExceptions() {
        String[] expressionsWithExceptions = {
                "2/0",
                "sqrt(-1)",
                "((2+1)",
                "1..01 + 2",
                "1.1!",
                "1,1 + 2,2",
                "-1/-1.-log(1,2,3)",
                "(1.,-.1)",
                "(,1.,-.1)",
                "(,1.,-.1,)",
                "(,1.,-.1,)π",
                "(0.9)π^",
                "(0.9)π^-",
                "(0.9)π^-log(2,2,2,2)------------",
                "(0.9)π^-log(5,4,3,2,2)--+-*/",
                "(0.9)π^-log(5,4,3,2,2)--+-(1)",
                "(0.9)7^----(1)"
        };

        for (String expression : expressionsWithExceptions) {
            try {
                ArrayList<CalculatorToken> t = Calculator.tokenize(expression);
                Queue<CalculatorToken> rpn = Calculator.sortMachineAlgo(t);
                Calculator.evaluate(rpn);

                // Если мы дошли сюда, исключение не было брошено - тест должен упасть
                fail("Ожидалось исключение для выражения: " + expression);
            } catch (CalculatorException e) {
                // Исключение было брошено - тест проходит
                assertTrue(true);
            } catch (Exception e) {
                // Любое другое исключение - тест должен упасть
                fail("Для выражения '" + expression + "' ожидалось CalculatorException, но получено: " +
                        e.getClass().getSimpleName());
            }
        }
    }
}