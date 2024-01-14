package lab2;

import javax.swing.*;
import java.awt.*;

public class HelloJavaComponent extends JComponent {
    public static final int MES_X = 20;
    public static final int MES_Y = 20;
    //Определяем координаты левой верхней точки прямоугольника содержащег компонент относительно левой верхней точки фрейма
    private static final int DEF_WIDTH = 200;
    private static final int DEF_HEIGHT = 100;

    //Определяем предпочтительные размеры прямоугольника, содержащего компонент
    public void paintComponent(Graphics g) {
        g.drawString("Hallo Java", MES_X, MES_Y);
    }

    //Метод возвращает размеры компонента
    public Dimension getPreferredSize() {
        return new Dimension(DEF_WIDTH, DEF_HEIGHT);

    }
}