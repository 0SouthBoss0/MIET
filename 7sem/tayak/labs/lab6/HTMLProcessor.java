import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.regex.*;

class HTMLProcessor {

    public enum TextAlignment {
        LEFT, CENTER, RIGHT
    }

    public static class TextStyle {
        String color = "white";
        String bgColor = "black";
        TextAlignment alignment = TextAlignment.LEFT;
        boolean bold = false;
        boolean italic = false;
        boolean underline = false;

        public TextStyle copy() {
            TextStyle copy = new TextStyle();
            copy.color = this.color;
            copy.bgColor = this.bgColor;
            copy.alignment = this.alignment;
            copy.bold = this.bold;
            copy.italic = this.italic;
            copy.underline = this.underline;
            return copy;
        }
    }


    private final Stack<Block> blockStack = new Stack<>();
    private final Block rootBlock;
    private final List<String> errors = new ArrayList<>();
    private final int consoleWidth = 80;
    private final int consoleHeight = 100;
    private final ScreenCell[][] screenBuffer;
    private int currentLine = 0;
    private int currentColumn = 0;

    private static final Map<String, String> COLOR_CODES = new HashMap<>();
    private static final Map<String, String> BG_COLOR_CODES = new HashMap<>();

    static {
        COLOR_CODES.put("black", "30");
        COLOR_CODES.put("red", "31");
        COLOR_CODES.put("green", "32");
        COLOR_CODES.put("yellow", "33");
        COLOR_CODES.put("blue", "34");
        COLOR_CODES.put("magenta", "35");
        COLOR_CODES.put("cyan", "36");
        COLOR_CODES.put("white", "37");
        COLOR_CODES.put("gray", "90");
        COLOR_CODES.put("bright_red", "91");
        COLOR_CODES.put("bright_green", "92");
        COLOR_CODES.put("bright_yellow", "93");
        COLOR_CODES.put("bright_blue", "94");
        COLOR_CODES.put("bright_magenta", "95");
        COLOR_CODES.put("bright_cyan", "96");
        COLOR_CODES.put("bright_white", "97");
        BG_COLOR_CODES.put("black", "40");
        BG_COLOR_CODES.put("red", "41");
        BG_COLOR_CODES.put("green", "42");
        BG_COLOR_CODES.put("yellow", "43");
        BG_COLOR_CODES.put("blue", "44");
        BG_COLOR_CODES.put("magenta", "45");
        BG_COLOR_CODES.put("cyan", "46");
        BG_COLOR_CODES.put("white", "47");
        BG_COLOR_CODES.put("gray", "100");
        BG_COLOR_CODES.put("bright_red", "101");
        BG_COLOR_CODES.put("bright_green", "102");
        BG_COLOR_CODES.put("bright_yellow", "103");
        BG_COLOR_CODES.put("bright_blue", "104");
        BG_COLOR_CODES.put("bright_magenta", "105");
        BG_COLOR_CODES.put("bright_cyan", "106");
        BG_COLOR_CODES.put("bright_white", "107");
    }

    public HTMLProcessor() {
        rootBlock = new Block("root");
        blockStack.push(rootBlock);
        screenBuffer = new ScreenCell[consoleHeight][consoleWidth];
        for (int i = 0; i < consoleHeight; i++) {
            for (int j = 0; j < consoleWidth; j++) {
                screenBuffer[i][j] = new ScreenCell();
            }
        }
    }

    private void drawBorder() {
        for (int j = 0; j < consoleWidth; j++) {
            if (j == 0) {
                screenBuffer[0][j].character = '┌';
            } else if (j == consoleWidth - 1) {
                screenBuffer[0][j].character = '┐';
            } else {
                screenBuffer[0][j].character = '─';
            }
        }
        for (int j = 0; j < consoleWidth; j++) {
            if (j == 0) {
                screenBuffer[consoleHeight - 1][j].character = '└';
            } else if (j == consoleWidth - 1) {
                screenBuffer[consoleHeight - 1][j].character = '┘';
            } else {
                screenBuffer[consoleHeight - 1][j].character = '─';
            }
        }
        for (int i = 1; i < consoleHeight - 1; i++) {
            screenBuffer[i][0].character = '│';
            screenBuffer[i][consoleWidth - 1].character = '│';
        }
    }

    private void clearScreenBuffer() {
        for (int i = 0; i < consoleHeight; i++) {
            for (int j = 0; j < consoleWidth; j++) {
                screenBuffer[i][j] = new ScreenCell();
            }
        }
    }

    public void processHTML(String html) {
        String pattern = "(<[^>]+>)|([^<]+)";
        Pattern r = Pattern.compile(pattern);
        Matcher m = r.matcher(html);

        while (m.find()) {
            if (m.group(1) != null) {
                String tag = m.group(1);
                processTag(tag);
            } else if (m.group(2) != null) {
                String text = m.group(2).trim();
                if (!text.isEmpty()) {
                    processText(text);
                }
            }
        }
        if (blockStack.size() > 1) {
            errors.add("Найдены незакрытые теги");
        }
    }

    private void processTag(String tag) {
        if (tag.startsWith("</")) {
            String tagName = tag.substring(2, tag.length() - 1).toLowerCase().trim();
            closeTag(tagName);
        } else if (tag.startsWith("<!--")) {
            return;
        } else {
            String tagContent = tag.substring(1, tag.length() - 1);
            processOpeningTag(tagContent);
        }
    }

    private void processOpeningTag(String tagContent) {
        String[] parts = tagContent.split("\\s+", 2);
        String tagName = parts[0].toLowerCase();
        Map<String, String> attributes = new HashMap<>();

        if (parts.length > 1) {
            String attrString = parts[1];
            Pattern attrPattern = Pattern.compile("(\\w+)\\s*=\\s*\"([^\"]*)\"");
            Matcher attrMatcher = attrPattern.matcher(attrString);

            while (attrMatcher.find()) {
                attributes.put(attrMatcher.group(1).toLowerCase(),
                        attrMatcher.group(2));
            }
        }

        Block newBlock = new Block(tagName);
        newBlock.attributes = attributes;

        newBlock.style = blockStack.peek().style.copy();
        applyStylesFromAttributes(newBlock.style, attributes);
        blockStack.peek().children.add(newBlock);
        blockStack.push(newBlock);
        if (isSelfClosingTag(tagName)) {
            blockStack.pop();
        }
    }

    private void applyStylesFromAttributes(TextStyle style, Map<String, String> attributes) {
        for (Map.Entry<String, String> entry : attributes.entrySet()) {
            String key = entry.getKey();
            String value = entry.getValue();

            switch (key) {
                case "color":
                    style.color = value;
                    break;
                case "bgcolor":
                case "background":
                    style.bgColor = value;
                    break;
                case "align":
                    if ("center".equalsIgnoreCase(value)) {
                        style.alignment = TextAlignment.CENTER;
                    } else if ("right".equalsIgnoreCase(value)) {
                        style.alignment = TextAlignment.RIGHT;
                    } else {
                        style.alignment = TextAlignment.LEFT;
                    }
                    break;
                case "bold":
                    style.bold = Boolean.parseBoolean(value);
                    break;
                case "italic":
                    style.italic = Boolean.parseBoolean(value);
                    break;
                case "underline":
                    style.underline = Boolean.parseBoolean(value);
                    break;
            }
        }
    }

    private boolean isSelfClosingTag(String tagName) {
        return tagName.equals("br") || tagName.equals("hr") ||
                tagName.equals("img") || tagName.equals("input");
    }

    private void closeTag(String tagName) {
        if (blockStack.size() <= 1) {
            errors.add("Лишний закрывающий тег: </" + tagName + ">");
            return;
        }

        Block currentBlock = blockStack.peek();
        if (!currentBlock.tagName.equals(tagName)) {
            errors.add("Несоответствие тегов: ожидается </" + currentBlock.tagName +
                    ">, найден </" + tagName + ">");
        }

        blockStack.pop();
    }

    private void processText(String text) {
        TextStyle currentStyle = blockStack.peek().style.copy();
        blockStack.peek().children.add(new TextNode(text, currentStyle));
    }

    public void render() {
        System.out.println("=== РЕНДЕРИНГ HTML ДОКУМЕНТА ===\n");

        if (!errors.isEmpty()) {
            System.out.println("Ошибки при обработке:");
            for (String error : errors) {
                System.out.println("  - " + error);
            }
            System.out.println();
        }
        clearScreenBuffer();

        currentLine = 1;
        currentColumn = 1;
        drawBorder();
        renderBlock(rootBlock, 0);
        printScreenBuffer();
    }

    private void printScreenBuffer() {
        String lastColorCode = "";

        for (int i = 0; i < consoleHeight; i++) {
            StringBuilder line = new StringBuilder();

            for (int j = 0; j < consoleWidth; j++) {
                ScreenCell cell = screenBuffer[i][j];
                String cellColorCode = cell.getANSICode();
                if (!cellColorCode.equals(lastColorCode)) {
                    line.append(cellColorCode);
                    lastColorCode = cellColorCode;
                }

                line.append(cell.character);
            }
            line.append("\u001B[0m");
            System.out.print(line.toString());
            if (i < consoleHeight - 1) {
                System.out.println();
            }
        }
    }

    private void renderBlock(Block block, int level) {
        if (!block.tagName.equals("root")) {
            renderBlockDecoration(block, level);
        }

        for (Object child : block.children) {
            if (child instanceof TextNode) {
                renderTextNode((TextNode) child, level);
            } else if (child instanceof Block) {
                renderBlock((Block) child, level);
            }
        }

        if (!block.tagName.equals("root")) {
            renderBlockEnd(block, level);
        }
    }

    private void renderBlockDecoration(Block block, int level) {
        if (currentLine >= consoleHeight - 1) return;

        int indent = level * 2;
        int startCol = 1 + indent;
        int availableWidth = consoleWidth - 2 - indent;

        switch (block.tagName) {
            case "h1":
                if (currentLine < consoleHeight - 1) {
                    String line = "═".repeat(Math.max(0, availableWidth));
                    writeTextToBuffer(currentLine, startCol, line, block.style);
                    currentLine++;
                }
                break;

            case "h2":
                if (currentLine < consoleHeight - 1) {
                    String line = "─".repeat(Math.max(0, availableWidth));
                    writeTextToBuffer(currentLine, startCol, line, block.style);
                    currentLine++;
                }
                break;

            case "hr":
                if (currentLine < consoleHeight - 1) {
                    String line = "─".repeat(Math.max(0, availableWidth));
                    writeTextToBuffer(currentLine, startCol, line, block.style);
                    currentLine++;
                }
                break;

            case "br":
                if (currentLine < consoleHeight - 1) {
                    currentLine++;
                    currentColumn = 1 + level * 2;
                }
                break;
        }
    }

    private void renderBlockEnd(Block block, int level) {
        if (currentLine >= consoleHeight - 1) return;

        switch (block.tagName) {
            case "h1":
            case "h2":
                if (currentLine < consoleHeight - 1) {
                    currentLine++;
                    currentColumn = 1 + level * 2;
                }
                break;
        }
    }

    private void renderTextNode(TextNode node, int level) {
        if (node.text.trim().isEmpty() || currentLine >= consoleHeight - 1) {
            return;
        }

        String text = node.text;
        int indent = level * 2;
        currentColumn = 1 + indent;
        String[] words = text.split("\\s+");
        int availableWidth = consoleWidth - 2 - indent;
        List<String> lines = new ArrayList<>();
        StringBuilder currentLineText = new StringBuilder();

        for (String word : words) {
            if (currentLineText.length() + word.length() + 1 > availableWidth) {
                lines.add(currentLineText.toString());
                currentLineText = new StringBuilder(word);
            } else {
                if (currentLineText.length() > 0) {
                    currentLineText.append(" ");
                }
                currentLineText.append(word);
            }
        }
        if (currentLineText.length() > 0) {
            lines.add(currentLineText.toString());
        }
        for (String lineText : lines) {
            if (currentLine >= consoleHeight - 1) break;

            String formattedLine = formatLine(lineText, node.style.alignment, availableWidth);
            int startCol = calculateStartColumn(formattedLine, node.style.alignment, indent, availableWidth);

            writeTextToBuffer(currentLine, startCol, formattedLine, node.style);
            currentLine++;
            currentColumn = 1 + indent;
        }
    }

    private String formatLine(String line, TextAlignment alignment, int width) {
        return line;
    }

    private int calculateStartColumn(String line, TextAlignment alignment, int indent, int availableWidth) {
        int startCol = 1 + indent;

        switch (alignment) {
            case CENTER:
                int padding = (availableWidth - line.length()) / 2;
                startCol += padding;
                break;

            case RIGHT:
                startCol += availableWidth - line.length();
                break;

            case LEFT:
            default:
                break;
        }

        return Math.max(1 + indent, Math.min(startCol, consoleWidth - 1 - line.length()));
    }

    private void writeTextToBuffer(int lineNum, int startCol, String text, TextStyle style) {
        if (lineNum < 0 || lineNum >= consoleHeight) return;

        String colorCode = COLOR_CODES.getOrDefault(style.color.toLowerCase(), "37");
        String bgColorCode = BG_COLOR_CODES.getOrDefault(style.bgColor.toLowerCase(), "40");

        for (int i = 0; i < text.length(); i++) {
            int col = startCol + i;
            if (col >= consoleWidth - 1) break;

            ScreenCell cell = screenBuffer[lineNum][col];
            cell.character = text.charAt(i);
            cell.colorCode = colorCode;
            cell.bgColorCode = bgColorCode;
            cell.bold = style.bold;
            cell.italic = style.italic;
            cell.underline = style.underline;
        }
    }

    public static void main(String[] args) {
        HTMLProcessor processor = new HTMLProcessor();

        try {
            Path inputPath = Paths.get("./src/input.txt");
            String htmlContent = new String(Files.readAllBytes(inputPath));

            System.out.println("Обработка HTML документа...");
            processor.processHTML(htmlContent);
            processor.render();

        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла: " + e.getMessage());
        }
    }
}