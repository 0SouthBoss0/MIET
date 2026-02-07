import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Программа работы магазинного автомата");
        System.out.println("=====================================");

        try {
            // Создание автомата
            MagazineAutomation automaton = new MagazineAutomation();

            // Загрузка грамматики
            String grammarFile = "./src/grammar.txt";
            automaton.buildFromGrammar(grammarFile);

            // Ввод строки для анализа
            System.out.print("Введите строку для анализа: ");
            String inputString = scanner.nextLine();

            System.out.println();

            // Вывод информации об автомате (для оценки "отлично")
            automaton.printAutomatonInfo();

            // Анализ строки с выводом трассировки
            MagazineAutomation.AcceptanceResult result = automaton.acceptsWithTrace(inputString, true);

            System.out.println("=== РЕЗУЛЬТАТ АНАЛИЗА ===");
            System.out.println("Цепочка: " + inputString);
            System.out.println("Результат: " + (result.accepted ? "ДОПУСТИМА" : "НЕДОПУСТИМА"));

            if (result.accepted) {
                System.out.println("\n=== ПОСЛЕДОВАТЕЛЬНОСТЬ КОНФИГУРАЦИЙ ===");
                for (int i = 0; i < result.configurations.size(); i++) {
                    System.out.println(i + ": " + result.configurations.get(i));
                }
            }

        } catch (Exception e) {
            System.out.println("Ошибка: " + e.getMessage());
            e.printStackTrace();
        } finally {
            scanner.close();
        }
    }
}