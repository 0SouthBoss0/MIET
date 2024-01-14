package lab2;

public class Truck extends Vehicle {

    private int weight;
    private int height;

    public Truck(String model, int maxspeed, Radio radio, int weight, int height) {
        super(model, maxspeed, radio);
        this.weight = weight;
        this.height = height;
    }

    public Truck() {
        super();
        weight = 0;
        height = 0;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    @Override
    public void move() {
        System.out.println(this.getModel() + " едет со скоростью " + this.getMaxspeed() + ". Вес: " + this.getWeight() + ". Высота: " + this.getHeight());
    }
}
