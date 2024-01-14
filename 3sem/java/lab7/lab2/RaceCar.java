package lab2;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class RaceCar extends Thread {
    private int team;
    private int speed;
    private Color color;
    private RaceFrame raceFrame;
    private JButton button;
    private int minspeed = 10;
    private int maxspeed = 20;


    public RaceCar(int team, Color color, RaceFrame raceFrame) {
        Random rn = new Random();
        this.raceFrame = raceFrame;
        this.team = team;
        this.color = color;
        speed = rn.nextInt(maxspeed - minspeed + 1) + minspeed;
        button = new JButton(String.valueOf(team));
        button.setBackground(color);

    }

    public JButton getButton() {
        return button;
    }

    @Override
    public void run() {
        int x = button.getLocation().x;
        int y = button.getLocation().y;
        while (RaceFrame.raceOn) {
            if (x < 1101) {
                try {
                    x += speed;
                    button.setLocation(x, y);
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } else {
                raceFrame.finishRace(color, team);
            }
        }
        System.out.printf("%s finished... \n", Thread.currentThread().getName());
    }
}
