import java.util.ArrayList;
import java.util.List;

public class ScreenCell {
    char character = ' ';
    String colorCode = "";
    String bgColorCode = "";
    boolean bold = false;
    boolean italic = false;
    boolean underline = false;

    String getANSICode() {
        StringBuilder code = new StringBuilder("\u001B[");
        code.append(colorCode).append(";").append(bgColorCode);

        List<String> styles = new ArrayList<>();
        if (bold) styles.add("1");
        if (italic) styles.add("3");
        if (underline) styles.add("4");

        if (!styles.isEmpty()) {
            code.append(";").append(String.join(";", styles));
        }

        code.append("m");
        return code.toString();
    }
}