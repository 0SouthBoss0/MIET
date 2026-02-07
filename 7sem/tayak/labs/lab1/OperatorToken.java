import java.util.HashMap;
import java.util.Map;

public class OperatorToken extends CalculatorToken {
    public int priority;

    public OperatorToken(String t_value) {
        super(t_value);
        switch (t_value) {
            case "+", "-":
                priority = 1;
                break;
            case "*", "/":
                priority = 2;
                break;
            case "^":
                priority = 3;
                break;
            case "~", "%":
                priority = 4;
                break;

        }
    }

    public String get_value() {
        return (String) t_value;
    }
}
