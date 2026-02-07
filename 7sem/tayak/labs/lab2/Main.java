import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    private final Automation automaton;

    public Main() {
        this.automaton = new Automation();
    }

    public void loadAutomatonFromFile(String filename) throws IOException {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            int lineNumber = 0;

            while ((line = reader.readLine()) != null) {
                lineNumber++;
                line = line.trim();

                if (line.isEmpty()) continue;

                try {
                    parseTransitionLine(line);
                } catch (Exception e) {
                    System.err.println("Ошибка в строке " + lineNumber + ": " + line);
                    System.err.println("Сообщение: " + e.getMessage());
                }
            }
        }
    }

    private void parseTransitionLine(String line) {
        String[] parts = line.split("=");
        if (parts.length != 2) {
            throw new IllegalArgumentException("Неверный формат строки");
        }

        String leftPart = parts[0];
        String rightPart = parts[1];

        String[] leftParts = leftPart.split(",");
        if (leftParts.length != 2) {
            throw new IllegalArgumentException("Неверный формат левой части");
        }

        String fromStateStr = leftParts[0];
        char symbol = leftParts[1].charAt(0);

        Node fromNode = new Node(fromStateStr);

        Node toNode = new Node(rightPart);
        Transition transition = new Transition(fromNode, toNode, symbol);
        automaton.addTransition(transition);
    }


    public static void main(String[] args) {
        Main main = new Main();

        try {
            main.loadAutomatonFromFile("./src/automation.txt");
            //main.loadAutomatonFromFile("./src/t2.txt");

            System.out.println("Исходный автомат:");
            main.automaton.printTransitions();

            System.out.println("\nДетерминированный?: " + main.automaton.isDeterministic());

            if (!main.automaton.isDeterministic()) {
                System.out.println("\nДетерминированный автомат:");
                Automation deterministic = main.automaton.determinize();
                deterministic.printTransitions();
            }
            Scanner in = new Scanner(System.in);
            while (true) {
                System.out.println("Введите строку");
               System.out.println( main.automaton.canParseString(in.nextLine()));
            }

        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла: " + e.getMessage());
        }
    }
}