import java.util.Random;
import java.util.Scanner;

public class Shell {
    static Scanner in = new Scanner(System.in);
    static Random rand = new Random();

    public static int randInt(int min, int max) {
        return rand.nextInt((max - min) + 1) + min;
    }

    public static void sort(int[] arr) {
        // расстояние между сравниваемыми элементами делится на 2 каждую итерацию
        for (int d = arr.length / 2; d > 0; d /= 2) {
            // сравнение элементов, находящихся на расстоянии d
            for (int i = d; i < arr.length; i += 1) {
                boolean flag = true;
                // сравниваем до тех пор, пока проводятся обмены
                while (flag) {
                    flag = false;
                    for (int j = d; j < arr.length; j += 1) {
                        // проводим обмен элементов по необходимости
                        if (arr[j] < arr[j - d]) {
                            int temp = arr[j];
                            arr[j] = arr[j - d];
                            arr[j - d] = temp;
                            flag = true;
                        }
                    }

                }

            }
            System.out.println("gap = " + d);
            for (int i = 0; i < arr.length; i++) {
                System.out.print(arr[i] + " ");
            }
            System.out.println();
        }
    }


    public static void main(String[] args) {
        System.out.println("Сортировка Шелла\nВведите размер массива:");

        // инициализация массива случайными значениями
        int length = in.nextInt();
        int[] array = new int[length];
        for (int i = 0; i < length; i++) {
            array[i] = randInt(1, 100);
        }

        // вывод исходного массива
        for (int i = 0; i < length; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println("\nХод сортировки:");
        sort(array);
        System.out.println("Массив отсортирован.");
    }
}
