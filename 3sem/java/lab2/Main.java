package lab2;

/*
Вариант № с_7.
1.	Разработать модель пропускного автомобильного пункта из следующих классов:
a.	Машина: марка машины, максимальная скорость, радио, метод Move.
b.	Радио: текущая станция, статус работы (вкл/выкл), метод PlayTunes.
c.	Грузовик: вес, высота кузова.
d.	Пункт ДПС, пропускающий определенные машины.

2.	Определить метод Pass, при вызове которого будет производиться анализ, пройдет ли контроль данный класс машины
(Пункт ДПС пропускает легковые и грузовые машины, едущие с определенным лимитом скорости;
грузовые машины должны соответствовать максимальным параметрам веса и высоты кузова).

3.	Разработать программу для демонстрации описанных классов.
*/


public class Main {

    public static void main(String[] args) {
        Car tesla = new Car("Tesla", 110, new Radio("Europa Plus", false));
        Car vaz = new Car("ВАЗ", 90, new Radio());
        Car bugatti = new Car("Bugatti", 240, new Radio("Радио Шансон", true));
        Truck scania = new Truck("Scania", 60, new Radio("Ретро ФМ", true), 4000, 300);
        Truck volvo = new Truck("Volvo", 80, new Radio("Релакс ФМ", false), 5000, 200);

        tesla.move();
        vaz.move();
        bugatti.move();
        scania.move();
        volvo.move();

        System.out.print("\n" + tesla.getModel() + ": ");
        tesla.getRadio().playTunes();

        System.out.print(vaz.getModel() + ": ");
        vaz.getRadio().playTunes();

        System.out.print(bugatti.getModel() + ": ");
        bugatti.getRadio().playTunes();

        System.out.print(scania.getModel() + ": ");
        scania.getRadio().playTunes();

        System.out.print(volvo.getModel() + ": ");
        volvo.getRadio().playTunes();

        PolicePoint policePoint = new PolicePoint(110, 4500, 300);

        System.out.println();
        policePoint.pass(tesla);
        policePoint.pass(vaz);
        policePoint.pass(bugatti);
        policePoint.pass(scania);
        policePoint.pass(volvo);
    }
}
