package lab2;

import java.util.Random;

public class ObjectGenerator {
    private static final String[] cars = {"Тойота", "Ниссан", "Хонда", "Мицубиси", "Мазда", "Субару", "Хендай", "Форд", "Фольксваген", "БМВ", "Киа", "Шевроле"};
    private static final String[] trucks = {"КАМАЗ", "МАЗ", "ЗИЛ", "Navistar", "Kenworth"};

    private static Random rand = new Random();

    public int getRandomInt(int start, int finish) {
        return rand.nextInt((finish - start) + 1) + start;
    }

    public Object generate() {
        return switch (getRandomInt(1, 3)) {
            case 1 -> new Car(cars[rand.nextInt(cars.length)], getRandomInt(60, 220), new Radio());
            case 2 -> new Truck(trucks[rand.nextInt(trucks.length)], getRandomInt(60, 150), new Radio(), getRandomInt(1000, 10000), getRandomInt(100, 500));
            case 3 -> new PolicePoint(getRandomInt(20, 150), getRandomInt(3000, 5000), getRandomInt(3000, 10000));
            default -> null;
        };
    }
}
