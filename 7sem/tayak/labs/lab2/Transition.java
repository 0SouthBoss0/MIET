public class Transition {
    public Node from;
    public Node to;
    public Character letter;


    public Transition(Node from, Node to, Character letter) {
        this.from = from;
        this.to = to;
        this.letter = letter;
    }

    @Override
    public String toString() {
        return from + "," + letter + "=" + to;
    }
}
