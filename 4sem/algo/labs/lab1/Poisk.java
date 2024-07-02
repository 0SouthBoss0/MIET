import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class Poisk {
    static Random rand = new Random();
    static Scanner in = new Scanner(System.in);

    public static int randInt(int min, int max) {
        return rand.nextInt((max - min) + 1) + min;
    }

    private static int binarySearch(int[] sortedArray, int valueToFind, int low, int high) {
        int index = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (sortedArray[mid] < valueToFind) {
                low = mid + 1;
            } else if (sortedArray[mid] > valueToFind) {
                high = mid - 1;
            } else if (sortedArray[mid] == valueToFind) {
                index = mid;
                break;
            }
        }
        return index;
    }

    public static void main(String[] args) {
        System.out.println("Бинарный поиск\nВведите размер массива:");

        // инициализация массива случайными значениями
        int length = in.nextInt();
        int[] array = new int[length];

        for (int i = 0; i < length; i++) {
            array[i] = randInt(1, 100);
        }

        // сортировка массива
        Arrays.sort(array);

        for (int i = 0; i < length; i++) {
            System.out.print(array[i] + " ");
        }

        System.out.println("\nВведите ключ:");
        int k = in.nextInt();

        System.out.println("Индекс элемента: " + binarySearch(array, k, 0, array.length - 1));
    }
}