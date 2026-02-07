public class CalculatorToken {
    Object t_value;

    public CalculatorToken(Object t_value) {
        this.t_value = t_value;
    }

    @Override
    public boolean equals(Object object) {
        if (!(object instanceof CalculatorToken)) {
            return false;
        }
        CalculatorToken other = (CalculatorToken) object;

        // Сравниваем значения с помощью equals()
        if (t_value == null) {
            return other.t_value == null;
        }
        return t_value.equals(other.t_value);
    }

    public Object get_t_value() {
        return t_value;
    }
}
