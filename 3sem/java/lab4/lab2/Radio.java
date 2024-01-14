package lab2;

public class Radio {
    private String station;
    private boolean workstatus;

    public Radio(String station, boolean workstatus) {
        this.station = station;
        this.workstatus = workstatus;
    }

    public Radio() {
        station = null;
        workstatus = false;
    }

    public String getStation() {
        return station;
    }

    public void setStation(String station) {
        this.station = station;
    }

    public boolean isWorkStatus() {
        return workstatus;
    }

    public void setWorkStatus(boolean workstatus) {
        this.workstatus = workstatus;
    }

    public void playTunes() {
        workstatus = true;
        if (station == null) {
            System.out.println("Нет радио");
        } else {
            System.out.println("Играет станция: " + station);
        }
    }

}
