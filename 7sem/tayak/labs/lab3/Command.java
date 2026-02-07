public class Command {
    String state;
    String inputSymbol;
    String stackSymbol;
    String newState;
    String newStackSymbols;

    public Command(String state, String inputSymbol, String stackSymbol, String newState, String newStackSymbols) {
        this.state = state;
        this.inputSymbol = inputSymbol;
        this.stackSymbol = stackSymbol;
        this.newState = newState;
        this.newStackSymbols = newStackSymbols;
    }

    @Override
    public String toString() {
        return String.format("δ(%s, %s, %s) = (%s, %s)", state, inputSymbol, stackSymbol, newState, newStackSymbols);
    }
}