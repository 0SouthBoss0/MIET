package lab2;

public class PolicePoint {

    private int speedlimit;
    private int weightlimit;
    private int heightlimit;

    public PolicePoint(int speedlimit, int weightlimit, int heightlimit) {
        this.speedlimit = speedlimit;
        this.weightlimit = weightlimit;
        this.heightlimit = heightlimit;
    }

    public PolicePoint() {
        speedlimit = 110;
        weightlimit = 5000;
        heightlimit = 400;
    }

    public boolean pass(Car car) {
        if (car.getMaxspeed() <= speedlimit) {
            System.out.println(car.getModel() + " проехала успешно. Скорость: " + car.getMaxspeed());
            return true;
        }
        System.out.println(car.getModel() + " остановлена. Скорость: " + car.getMaxspeed() + " больше разрешённой: " + speedlimit);
        return false;
    }

    public boolean pass(Truck truck) {
        if (truck.getMaxspeed() <= speedlimit && truck.getWeight() <= weightlimit && truck.getHeight() <= heightlimit) {
            System.out.println(truck.getModel() + " проехал успешно. Скорость: " + truck.getMaxspeed() + " Вес: " + truck.getWeight() + " Высота: " + truck.getHeight());
            return true;
        }

        System.out.println(truck.getModel() + " остановлена.");
        if (truck.getMaxspeed() > speedlimit) {
            System.out.println("Скорость: " + truck.getMaxspeed() + " больше разрешённой: " + speedlimit);
        }

        if (truck.getWeight() > weightlimit) {
            System.out.println("Вес: " + truck.getWeight() + " больше разрешённого: " + weightlimit);
        }

        if (truck.getHeight() > heightlimit) {
            System.out.println("Высота " + truck.getHeight() + " больше разрешённой: " + getHeightlimit());
        }
        return false;
    }

    public int getSpeedlimit() {
        return speedlimit;
    }

    public void setSpeedlimit(int speedlimit) {
        this.speedlimit = speedlimit;
    }

    public int getWeightlimit() {
        return weightlimit;
    }

    public void setWeightlimit(int weightlimit) {
        this.weightlimit = weightlimit;
    }

    public int getHeightlimit() {
        return heightlimit;
    }

    public void setHeightlimit(int heightlimit) {
        this.heightlimit = heightlimit;
    }

    public void info(){
        System.out.println("Пункт ДПС. Предел скорости: " + speedlimit + ", предел веса: " + weightlimit + ", предел высоты: " + heightlimit);
    }
}
