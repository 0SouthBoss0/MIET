package lab2;

public abstract class Vehicle {

    private String model;
    private int maxspeed;
    private Radio radio;

    public Vehicle(String model, int maxspeed, Radio radio){
        this.model = model;
        this.maxspeed = maxspeed;
        this.radio = radio;
    }

    public Vehicle(){
        model = null;
        maxspeed = 0;
        radio = new Radio();
    }

    public abstract void move();

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public int getMaxspeed() {
        return maxspeed;
    }

    public void setMaxspeed(int maxspeed) {
        this.maxspeed = maxspeed;
    }

    public Radio getRadio() {
        return radio;
    }

    public void setRadio(Radio radio) {
        this.radio = radio;
    }

}
