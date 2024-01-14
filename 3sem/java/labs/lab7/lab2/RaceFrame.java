package lab2;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.text.html.ImageView;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class RaceFrame extends JFrame {

    private static List<RaceCar> racecars = new ArrayList<>();
    public static boolean raceOn = false;
    public static boolean raceReady = false;




    public JLayeredPane panel;
    public static RaceComponent raceComponent = new RaceComponent();
    public static JButton restartButton = new JButton("НА СТАРТ");
    public static JButton startButton = new JButton("СТАРТ");


    public RaceFrame(int width, int height) {
        panel = new JLayeredPane();
        panel.setLayout(null);

        // добавление трассы
        raceComponent.setBounds(0, 0, width - raceComponent.squaresize, height);
        panel.add(raceComponent, 1, 0);

        // кнопка рестарта
        restartButton.setBounds(300, 600, raceComponent.squaresize * 9, raceComponent.squaresize * 3);
        panel.add(restartButton, 2, 0);

        // кнопка старта
        startButton.setBounds(700, 600, raceComponent.squaresize * 9, raceComponent.squaresize * 3);
        panel.add(startButton, 2, 0);

        Container c = getContentPane();
        c.add(panel);

        restartButton.addActionListener(e -> {
            raceOn = false;
            try {
                Thread.sleep(50);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
            raceReady = true;
            getReady();
        });

        startButton.addActionListener(e -> {
            if (raceReady) {
                raceReady = false;
                raceOn = true;
                startRace();

            }
        });


        setSize(width, height);
        setResizable(false);
        setTitle("Лабораторная работа №7");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    public void getReady() {
        for (RaceCar raceCar : racecars) {
            raceCar.getButton().setVisible(false);
            raceCar.getButton().setBounds(0, 0, 0, 0);
        }
        // машины на старт
        RaceCar rc = new RaceCar(1, Color.RED, this);
        JButton button = rc.getButton();
        button.setBounds(0, 0, raceComponent.squaresize * 3, raceComponent.squaresize * 3);
        button.setVisible(true);
        panel.add(button, 2, 0);

        RaceCar rc2 = new RaceCar(2, Color.BLUE, this);
        JButton button2 = rc2.getButton();
        button2.setBounds(0, 125, raceComponent.squaresize * 3, raceComponent.squaresize * 3);
        button.setVisible(true);
        panel.add(button2, 2, 0);

        RaceCar rc3 = new RaceCar(3, Color.GREEN, this);
        JButton button3 = rc3.getButton();
        button3.setBounds(0, 250, raceComponent.squaresize * 3, raceComponent.squaresize * 3);
        panel.add(button3, 2, 0);

        RaceCar rc4 = new RaceCar(4, Color.YELLOW, this);
        JButton button4 = rc4.getButton();
        button4.setBounds(0, 375, raceComponent.squaresize * 3, raceComponent.squaresize * 3);
        panel.add(button4, 2, 0);

        RaceCar rc5 = new RaceCar(5, Color.ORANGE, this);
        JButton button5 = rc5.getButton();
        button5.setBounds(0, 500, raceComponent.squaresize * 3, raceComponent.squaresize * 3);
        panel.add(button5, 2, 0);

        racecars.clear();
        racecars.add(rc);
        racecars.add(rc2);
        racecars.add(rc3);
        racecars.add(rc4);
        racecars.add(rc5);


        raceComponent.setBackground(UIManager.getColor("raceComponent.background"));
    }

    public void startRace() {
        for (RaceCar racecar : racecars) {
            racecar.start();
        }

    }

    public void finishRace(Color color, int team) {
        raceOn = false;
        raceComponent.setBackground(color);
        raceReady = false;
        JOptionPane.showMessageDialog(null, "Победитель: Кнопка " + team);
    }
}
