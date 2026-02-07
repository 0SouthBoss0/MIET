import java.util.Objects;

public class Node {
    public String name;
    public boolean isFinal;

    public Node(String name) {
        this.name = name;
        this.isFinal = name.charAt(0) == 'f';
    }

    @Override
    public String toString() {
        return name;
    }
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Node node = (Node) o;
        return Objects.equals(name, node.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name);
    }
}
