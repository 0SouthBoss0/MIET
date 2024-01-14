import java.util.Scanner;

public class Main {
    public static int[] monthLengths =
            new int[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // проверка года на високосность
    public static boolean isLeapYear(int year) {
        if (year % 4 != 0) {
            return false;
        } else if (year % 400 == 0) {
            return true;
        } else
            return year % 100 != 0;
    }

    // модель
    static void model(int day, int month, int year) {
        int dayscount = 0;

        // добавление дней в полностью пройденнных месяцах
        for (int i = 0; i < month - 1; i++) {
            dayscount += monthLengths[i];
        }

        // добавление одного дня в случае високосного года
        if (month > 2 && isLeapYear(year)) {
            dayscount += 1;
        }

        // добавление дней в неполностью пройденном месяце
        dayscount += day - 1;
        view("Прошло дней с начала года: " + String.valueOf(dayscount));
    }

    // вид
    static void view(String output) {
        System.out.println(output);
    }

    // контроллер
    static void controller() {
        Scanner in = new Scanner(System.in);
        int temp1 = 0;
        int temp2 = 0;
        int temp3 = 0;

        // ввод дня
        while (true) {
            view("Введите число дня: ");
            String s = in.nextLine();
            try {
                temp1 = Integer.parseInt(s);
                // проверка валидности числа дней
                if (temp1 < 1 || temp1 > 31) {
                    throw new Exception();
                }
                break;

            } catch (Exception e) {
                view("Неккоректный ввод! ");
            }
        }

        // ввод месяца
        while (true) {
            view("Введите число месяца: ");
            String s = in.nextLine();
            try {
                temp2 = Integer.parseInt(s);
                // проверка валидности месяца
                if (temp2 < 1 || temp2 > 12) {
                    throw new Exception();
                }
                // проверка введеннного количества дней в введенном месяце
                int currentlength = monthLengths[temp2 - 1];
                // в феврале - потенциально 29 дней
                if (temp2 == 2) {
                    currentlength += 1;
                }
                if (temp1 > currentlength) {
                    throw new Exception();
                }
                break;

            } catch (Exception e) {
                view("Неккоректный ввод! ");
            }
        }

        // ввод года
        while (true) {
            view("Введите число года: ");
            String s = in.nextLine();
            try {
                temp3 = Integer.parseInt(s);
                // проверка введенного количества дней февраля для високосного года
                if (!isLeapYear(temp3) && temp1 > 28 && temp2 == 2) {
                    throw new Exception();
                }
                break;

            } catch (Exception e) {
                view("Неккоректный ввод! ");
            }
        }

        model(temp1, temp2, temp3);
    }

    public static void main(String[] args) {
        controller();
    }
}
