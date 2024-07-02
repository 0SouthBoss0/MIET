import java.util.Scanner;


public class Recursive {
    static Scanner in = new Scanner(System.in);

    public static int getFactorial(int x) {
        if (x <= 1) {
            return 1;
        }
        return x * getFactorial(x - 1);

    }

    public static int getPowerTwo(int x) {
        if (x == 0) {
            return 1;
        }
        return 2 * getPowerTwo(x - 1);
    }

    public static void main(String[] args) {
        System.out.println("Введите n:");
        int n = in.nextInt();

        // An = (n!) / (2^n)
        System.out.println("Факториал n = " + getFactorial(n));
        System.out.println("Два в степени n = " + getPowerTwo(n));
        float answer = (float) (getFactorial(n)) / (float) getPowerTwo(n);
        System.out.println("Ответ = " + answer);
    }
}