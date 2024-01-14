package lab2;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;


public class ObjectsList {
    public ArrayList<Object> myobjects = new ArrayList<>();

    // сохранить объекты в файл
    public void put() {
        File file = new File("database.txt");

        try (FileOutputStream fos = new FileOutputStream(file);
             OutputStreamWriter osw = new OutputStreamWriter(fos, StandardCharsets.UTF_8)) {

            int i = 0;
            for (Object o : myobjects) {
                if (o instanceof Car car) {
                    osw.write(i + "," + "car" + "," + car.getModel() + "," + car.getMaxspeed() + "," + car.getRadio().getStation() + "," + car.getRadio().isWorkStatus());
                }

                if (o instanceof Truck truck) {
                    osw.write(i + "," + "truck" + "," + truck.getModel() + "," + truck.getMaxspeed() + "," + truck.getWeight() + "," + truck.getHeight() + "," + truck.getRadio().getStation() + "," + truck.getRadio().isWorkStatus());
                }

                if (o instanceof PolicePoint policepoint) {
                    osw.write(i + "," + "policepoint" + "," + policepoint.getSpeedlimit() + "," + policepoint.getWeightlimit() + "," + policepoint.getHeightlimit());
                }
                i += 1;
                osw.write("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // получить объекты из файла
    public void get() throws FileNotFoundException {
        File file = new File("database.txt");
        FileInputStream fis = new FileInputStream(file);
        InputStreamReader in = new InputStreamReader(fis, StandardCharsets.UTF_8);
        BufferedReader input = new BufferedReader(in);

        try {
            String line = null;
            while ((line = input.readLine()) != null) {
                String[] lines = line.split(",");
                switch (lines[1]) {
                    case ("car") ->
                            myobjects.add(new Car(lines[2], Integer.parseInt(lines[3]), new Radio(lines[4], Boolean.parseBoolean(lines[5]))));
                    case ("truck") ->
                            myobjects.add(new Truck(lines[2], Integer.parseInt(lines[3]), new Radio(lines[6], Boolean.parseBoolean(lines[7])), Integer.parseInt(lines[4]), Integer.parseInt(lines[5])));
                    case ("policepoint") ->
                            myobjects.add(new PolicePoint(Integer.parseInt(lines[2]), Integer.parseInt(lines[3]), Integer.parseInt(lines[4])));
                }
            }


        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    // удалить объект по индексу
    public void delete(int index) {
        myobjects.remove(index);
    }

    // вывести информацию по всем объектам
    public void printInfo() {
        for (int i = 0; i < myobjects.size(); i++) {
            Object o = myobjects.get(i);
            System.out.print(i + 1 + ": ");
            if (o instanceof Car car) {
                car.move();
            }
            if (o instanceof Truck truck) {
                truck.move();
            }
            if (o instanceof PolicePoint policepoint) {
                policepoint.info();
            }
        }
    }
}