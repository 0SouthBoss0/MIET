package lab2;

import javax.swing.*;
import java.awt.*;

public class App {
    public static void create() {
        EventQueue.invokeLater(() -> {
            SimpleFrame frame = new SimpleFrame(1240, 700);
            frame.setTitle("Лабораторная работа №5");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);

        });
    }
}
