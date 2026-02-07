import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Block {
    List<Object> children = new ArrayList<>();
    HTMLProcessor.TextStyle style = new HTMLProcessor.TextStyle();
    String tagName = "";
    Map<String, String> attributes = new HashMap<>();

    public Block(String tagName) {
        this.tagName = tagName.toLowerCase();
    }
}