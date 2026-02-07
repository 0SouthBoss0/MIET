public class ForState {
    String var;
    int currentValue;
    int target;
    int loopStartPos;
    String loopStartProgram;
    int loopStartToken;

    ForState(String var, int currentValue, int target, int loopStartPos, String loopStartProgram, int loopStartToken) {
        this.var = var;
        this.currentValue = currentValue;
        this.target = target;
        this.loopStartPos = loopStartPos;
        this.loopStartProgram = loopStartProgram;
        this.loopStartToken = loopStartToken;
    }
}