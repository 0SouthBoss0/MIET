package lab2;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.LinkedList;
import java.util.Scanner;

public class Main {
    static Configger configger = new Configger("example.ini");
    static Logger logger = new Logger("log.txt", false);
    static Logger collectionslogger = new Logger("collectionslogger.log", true);
    static ObjectGenerator objectgenerator = new ObjectGenerator();
    static boolean isAdmin = false;
    static Scanner in = new Scanner(System.in);
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";

    // установить конфигурацию для пользователя
    public static void setUserConfig(Configger configger) throws IOException {
        configger.set("NAME", "Mikhail");
        configger.set("PASSWORD", String.valueOf(123456));
        configger.set("GROUP", "user");
        configger.set("DEBUG", String.valueOf(true));
        configger.set("AUTOTESTS", String.valueOf(false));
        configger.save();
    }

    // установить конфигурацию для администратора
    public static void setAdminConfig(Configger configger) throws IOException {
        configger.set("NAME", "Admin");
        configger.set("PASSWORD", String.valueOf(112233));
        configger.set("GROUP", "root");
        configger.set("DEBUG", String.valueOf(true));
        configger.set("AUTOTESTS", String.valueOf(true));
        configger.save();
    }

    // проверка валидности числа
    public static int isValidInteger(String message, int limit) {
        int number = -1;
        while (number < 0 || number > limit) {
            System.out.println(message);
            String temp = in.nextLine();
            try {
                number = Integer.parseInt(temp);
                if (number < 0 || number > limit) {
                    throw new Exception();
                }
            } catch (Exception e) {
                if (Boolean.parseBoolean(configger.get("DEBUG"))) {
                    logger.createLog("Ошибка ввода числа!");
                }
            }
        }
        return number;
    }

    // проверка валидности числа и соответствия требуемому интервалу
    public static int isValidNumber(String message, int left, int right) {
        int indexchosen = -1;
        while (indexchosen < left || indexchosen > right) {
            System.out.println(message);
            String temp = in.nextLine();
            try {
                indexchosen = Integer.parseInt(temp);
                if (indexchosen < left || indexchosen > right) {
                    throw new Exception();
                }
            } catch (Exception e) {
                if (Boolean.parseBoolean(configger.get("DEBUG"))) {
                    logger.createLog("Ошибка ввода числа!");
                }
            }
        }
        return indexchosen;
    }

    // добавление новой машины
    public static Car addCar() {
        System.out.println("Введите модель машины:");
        String model = in.nextLine();
        int speed = isValidInteger("Введите скорость машины:", 300);
        return new Car(model, speed, new Radio());
    }

    // добавление нового грузовика
    public static Truck addTruck() {
        System.out.println("Введите модель грузовика:");
        String model = in.nextLine();
        int speed = isValidInteger("Введите скорость грузовика:", 200);
        int weight = isValidInteger("Введите вес грузовика:", 10000);
        int height = isValidInteger("Введите высоту грузовика:", 500);
        return new Truck(model, speed, new Radio(), weight, height);
    }

    // добавление нового пункта ДПС
    public static PolicePoint addPolicePoint() {
        int speedlimit = isValidInteger("Введите предел скорости:", 300);
        int weightlimit = isValidInteger("Введите предел веса:", 10000);
        int heightlimit = isValidInteger("Введите предел высоты", 500);
        return new PolicePoint(speedlimit, weightlimit, heightlimit);
    }

    // вызов главного меню
    public static void callMenu() {
        System.out.println(ANSI_GREEN);
        System.out.println("Загрузить информацию из файла: .........................1");
        System.out.println("Распечатать информацию о всех объектах: ................2");
        System.out.println("Добавить новый объект: .................................3");
        System.out.println("Удалить объект: ........................................4");
        System.out.println("Обновить объект: .......................................5");
        System.out.println("Сохранение и завершение сессии: ........................0" + ANSI_RESET);
    }

    // вызов дополнительного меню
    public static void callAdminMenu() {
        System.out.println(ANSI_GREEN + "Включение/отключение режима отладки: ...................6");
        System.out.println("Включение/отключение режима автотестов: ................7" + ANSI_RESET);
    }

    public static ArrayList<Object> addListTest(int length) {
        int totaltime = 0;
        ArrayList<Object> arraylist = new ArrayList<>();

        for (int i = 0; i < length; i++) {
            long startTime = System.nanoTime();
            arraylist.add(objectgenerator.generate());
            long endTime = System.nanoTime();
            totaltime += endTime - startTime;
            //collectionslogger.createTimeLog("add", "new item", i, endTime - startTime);
        }

        collectionslogger.addEndLog("ARRAYLIST " + length + ":\naddTotalCount = " + length + "\n" + "addTotalTime = " + totaltime + "\n" + "addMedianTime = " + totaltime / length);
        return arraylist;
    }

    public static void deleteListTest(ArrayList<Object> arraylist) {
        int sizeofstartarray = arraylist.size();
        int totaltime = 0;

        for (int i = 0; i < sizeofstartarray / 10; i++) {
            long startTime = System.nanoTime();
            arraylist.remove(objectgenerator.getRandomInt(0, arraylist.size() - 1));
            long endTime = System.nanoTime();
            totaltime += endTime - startTime;
            //collectionslogger.createTimeLog("delete", "an item", i, endTime - startTime);
        }

        collectionslogger.addEndLog("ARRAYLIST " + sizeofstartarray + ":\nremoveTotalCount = " + sizeofstartarray / 10 + "\n" + "removeTotalTime = " + totaltime + "\n" + "removeMedianTime = " + totaltime / (sizeofstartarray / 10));
    }

    public static LinkedList<Object> addLinkedListTest(int length) {
        int totaltime = 0;
        LinkedList<Object> linkedlist = new LinkedList<>();

        for (int i = 0; i < length; i++) {
            long startTime = System.nanoTime();
            linkedlist.add(objectgenerator.generate());
            long endTime = System.nanoTime();
            totaltime += endTime - startTime;
            //collectionslogger.createTimeLog("add", "new item", i, endTime - startTime);
        }

        collectionslogger.addEndLog("LINKEDLIST " + length + ":\naddTotalCount = " + length + "\n" + "addTotalTime = " + totaltime + "\n" + "addMedianTime = " + totaltime / length);
        return linkedlist;
    }

    public static void deleteLinkedListTest(LinkedList<Object> linkedlist) {
        int sizeofstartarray = linkedlist.size();
        int totaltime = 0;

        for (int i = 0; i < sizeofstartarray / 10; i++) {
            long startTime = System.nanoTime();
            linkedlist.remove(objectgenerator.getRandomInt(0, linkedlist.size() - 1));
            long endTime = System.nanoTime();
            totaltime += endTime - startTime;
            //collectionslogger.createTimeLog("delete", "an item", i, endTime - startTime);
        }

        collectionslogger.addEndLog("LINKEDLIST " + sizeofstartarray + ":\nremoveTotalCount = " + sizeofstartarray / 10 + "\n" + "removeTotalTime = " + totaltime + "\n" + "removeMedianTime = " + totaltime / (sizeofstartarray / 10));
    }

    public static void makeTest() {
        // эксперимент с добавлением элементов для ArrayList
        ArrayList<Object> arraylist10 = addListTest(10);
        ArrayList<Object> arraylist100 = addListTest(100);
        ArrayList<Object> arraylist1000 = addListTest(1000);
        ArrayList<Object> arraylist10000 = addListTest(10000);
        ArrayList<Object> arraylist100000 = addListTest(100000);

        // эксперимент с удалением элементов для ArrayList
        deleteListTest(arraylist10);
        deleteListTest(arraylist100);
        deleteListTest(arraylist1000);
        deleteListTest(arraylist10000);
        deleteListTest(arraylist100000);

        // эксперимент с добавлением элементов для LinkedList
        LinkedList<Object> linkedlist10 = addLinkedListTest(10);
        LinkedList<Object> linkedlist100 = addLinkedListTest(100);
        LinkedList<Object> linkedlist1000 = addLinkedListTest(1000);
        LinkedList<Object> linkedlist10000 = addLinkedListTest(10000);
        LinkedList<Object> linkedlist100000 = addLinkedListTest(100000);

        // эксперимент с удалением элементов для LinkedList
        deleteLinkedListTest(linkedlist10);
        deleteLinkedListTest(linkedlist100);
        deleteLinkedListTest(linkedlist1000);
        deleteLinkedListTest(linkedlist10000);
        deleteLinkedListTest(linkedlist100000);

        collectionslogger.saveEndLog();
    }

    public static void makeDopTest(int value) {
        int totaltime = 0;
        ArrayList<Object> before = new ArrayList<>(value);
        for (int i = 0; i < value; i++) {
            long startTime = System.nanoTime();
            before.add(objectgenerator.generate());
            long endTime = System.nanoTime();
            totaltime += endTime - startTime;
        }
        System.out.println("Время до увеличения размера: " + totaltime/value);


        totaltime = 0;
        ArrayList<Object> after = new ArrayList<>((value * 3) / 2 + 1);
        for (int i = 0; i < (value * 3) / 2 + 1; i++) {
            long startTime = System.nanoTime();
            after.add(objectgenerator.generate());
            long endTime = System.nanoTime();
            totaltime += endTime - startTime;
        }
        System.out.println("Время после увеличения размера: " + totaltime/((value * 3) / 2 + 1));


    }

    public static void main(String[] args) throws IOException {
        //setUserConfig(configger);
        setAdminConfig(configger);

        ObjectsList objectslist = new ObjectsList();


        makeTest();
        makeDopTest(1000000);


        if (Boolean.parseBoolean(configger.get("DEBUG"))) {
            logger.createLog("Programm started. User: " + configger.get("NAME"));
        }

        // приветствие пользователя
        if (configger.get("NAME").equals("Admin") && configger.get("PASSWORD").equals("112233")) {
            System.out.println("Добро пожаловать в режим администратора, " + configger.get("NAME"));
            isAdmin = true;
        } else {
            System.out.println("Добро пожаловать, " + configger.get("NAME"));
        }

        boolean status = true;
        while (status) {
            int taskchosen = -1;
            while (taskchosen == -1) {
                callMenu();
                if (isAdmin) {
                    callAdminMenu();
                }
                String temp = in.nextLine();
                try {
                    taskchosen = Integer.parseInt(temp);
                    if ((!isAdmin) && (taskchosen < 0 || taskchosen > 5) || (isAdmin) && (taskchosen < 0 || taskchosen > 7)) {
                        throw new Exception();
                    }
                } catch (Exception e) {
                    if (Boolean.parseBoolean(configger.get("DEBUG"))) {
                        logger.createLog("Ошибка ввода в меню!");
                    }
                }
            }

            switch (taskchosen) {
                // сохранение и завершение сессии
                case 0 -> {
                    objectslist.put();
                    status = false;
                    if (Boolean.parseBoolean(configger.get("DEBUG"))) {
                        logger.createLog("Programm finished.");
                    }
                }
                // загрузить информацию из файла
                case 1 -> {
                    objectslist.get();
                    if (Boolean.parseBoolean(configger.get("DEBUG"))) {
                        logger.createLog("Data from database uploaded.");
                    }
                }

                // распечатать информацию о всех объектах
                case 2 -> objectslist.printInfo();

                // добавить новый объект
                case 3 -> {
                    int indexchosen = isValidNumber("Выберите тип нового объекта (1-машина, 2-грузовик, 3-пункт ДПС):", 1, 3);
                    switch (indexchosen) {
                        case 1 -> objectslist.myobjects.add(addCar());
                        case 2 -> objectslist.myobjects.add(addTruck());
                        case 3 -> objectslist.myobjects.add(addPolicePoint());
                    }
                    if (Boolean.parseBoolean(configger.get("DEBUG"))) {
                        logger.createLog("Object loaded to database.");
                    }

                }
                // удалить объект
                case 4 -> {
                    int indexchosen = isValidNumber("Введите номер объекта для удаления:", 1, objectslist.myobjects.size());
                    objectslist.delete(indexchosen - 1);
                    if (Boolean.parseBoolean(configger.get("DEBUG"))) {
                        logger.createLog("Object deleted from database.");

                    }
                }
                // обновить объект
                case 5 -> {
                    int indexchosen = isValidNumber("Введите номер объекта для обновления:", 1, objectslist.myobjects.size());
                    if (objectslist.myobjects.get(indexchosen - 1) instanceof Car) {
                        objectslist.myobjects.set(indexchosen - 1, addCar());
                    }
                    if (objectslist.myobjects.get(indexchosen - 1) instanceof Truck) {
                        objectslist.myobjects.set(indexchosen - 1, addTruck());
                    }
                    if (objectslist.myobjects.get(indexchosen - 1) instanceof PolicePoint) {
                        objectslist.myobjects.set(indexchosen - 1, addPolicePoint());
                    }
                    if (Boolean.parseBoolean(configger.get("DEBUG"))) {
                        logger.createLog("Object updated from database.");
                    }

                }
                // отладка
                case 6 -> {
                    if (isAdmin) {
                        if (Boolean.parseBoolean(configger.get("DEBUG"))) {
                            configger.set("DEBUG", "false");
                            configger.save();
                            System.out.println("Режим отладки выключен");
                        } else {
                            configger.set("DEBUG", "true");
                            configger.save();
                            System.out.println("Режим отладки включен");
                        }

                    }
                }
                // автотесты
                case 7 -> {
                    if (isAdmin) {
                        if (Boolean.parseBoolean(configger.get("AUTOTESTS"))) {
                            configger.set("AUTOTESTS", "false");
                            configger.save();
                            System.out.println("Режим автотестов выключен");
                        } else {
                            configger.set("AUTOTESTS", "true");
                            configger.save();
                            System.out.println("Режим автотестов включен");
                        }

                    }
                }
            }
        }

    }
}
