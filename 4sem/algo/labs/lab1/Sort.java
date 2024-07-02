import java.util.Random;
import java.util.Scanner;

public class Sort {
    static Random rand = new Random();
    static Scanner in = new Scanner(System.in);

    public static int randInt(int min, int max) {
        return rand.nextInt((max - min) + 1) + min;
    }

    public static void binaryInsertionSort(int[] array) {
        for (int i = 1; i < array.length; i++) {
            // вывод текущей итерации
            for (int j = 0; j < array.length; j++) {
                if (i == j) {
                    System.out.print("\u001B[32m" + array[j] + "\u001B[0m" + " ");
                } else {
                    System.out.print(array[j] + " ");
                }
            }
            System.out.println("");


            // если текущий элемент меньше предыдущего
            if (array[i] < array[i - 1]) {
                // находим индекс для вставки бинарным поиском
                int low = 0;
                int high = i - 1;
                while (low < high) {
                    int mid = low + (high - low) / 2;
                    if (array[i] < array[mid]) {
                        high = mid;
                    } else {
                        low = mid + 1;
                    }
                }
                // вставляем со сдвигом
                int temp = array[i];
                for (int k = i - 1; k >= low; k--) {
                    array[k + 1] = array[k];
                }
                array[low] = temp;
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("Сортировка бинарной вставкой\nВведите размер массива:");

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
        binaryInsertionSort(array);

        // вывод отсортированного массива
        for (int i = 0; i < length; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println("\nМассив отсортирован.");
    }
}