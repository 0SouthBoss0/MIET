public class DigitToken extends CalculatorToken {
    public DigitToken(Double t_value) {
        super(t_value);
    }

    public double get_value() {
        return (Double) t_value;
    }
}
