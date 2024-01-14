package lab2;

public class Car extends Vehicle {

    public Car(String model, int maxspeed, Radio radio) {
        super(model, maxspeed, radio);
    }

    public Car() {
        super();
    }

    @Override
    public void move() {
        System.out.println(this.getModel() + " едет со скоростью " + this.getMaxspeed());
    }

}
