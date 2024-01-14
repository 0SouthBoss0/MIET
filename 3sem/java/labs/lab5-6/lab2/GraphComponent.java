package lab2;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import java.util.List;

public class GraphComponent extends JPanel {
    List<Integer> y_axis;
    int mar = 25;
    int DEF_N = 6;
    int POINT_SIZE = 10;

    public GraphComponent(List<Integer> y_axis) {
        this.y_axis = y_axis;
    }

    public void paintComponent(Graphics g) {
        int width = getWidth();
        int height = getHeight();
        super.paintComponent(g);


        Graphics2D graphics2D = (Graphics2D) g;
        g.setFont(new Font("TimesRoman", Font.PLAIN, 10));

        // отрисовка оси oX
        graphics2D.draw(new Line2D.Double(mar, height - mar, width - mar, height - mar));
        graphics2D.draw(new Line2D.Double(width - mar, height - mar, width - 1.1 * mar, height - 1.1 * mar));
        graphics2D.draw(new Line2D.Double(width - mar, height - mar, width - 1.1 * mar, height - 0.9 * mar));

        // отрисовка оси oY
        graphics2D.draw(new Line2D.Double(mar, mar, mar, height - mar));
        graphics2D.draw(new Line2D.Double(mar, mar, 1.1 * mar, 1.1 * mar));
        graphics2D.draw(new Line2D.Double(mar, mar, 0.9 * mar, 1.1 * mar));

        // отрисовка точек на координатной оси oX
        for (int i = 1; i < y_axis.size() + 1; i += 1) {
            Rectangle2D rectangle2D = new Rectangle(mar + i * (width - 2 * mar) / 7, height - mar - POINT_SIZE/2 , 1, 10);
            g.drawString(String.valueOf((int) Math.pow(10, i)), mar + i * (width - 2 * mar) / 7 - (4 * String.valueOf((int) Math.pow(10, i)).length() / 2), height - mar - POINT_SIZE / 2 + 2 * POINT_SIZE);
            graphics2D.fill(rectangle2D);
        }

        double del = height - mar - POINT_SIZE / 2 - (height - 2.5 * mar);
        double part = (height - mar - del) / DEF_N;

        // отрисовка точек на координатной оси oY
        for (int i = 0; i < DEF_N; i++) {
            Rectangle2D rectangle2D = new Rectangle(mar - POINT_SIZE / 2, (int) (del + i * part) + POINT_SIZE/2, 10, 1);
            long t = ((long) DEF_N - i) * getMax() / DEF_N;
            g.drawString(String.valueOf(t), mar + POINT_SIZE / 2, (int) (del + i * part));
            graphics2D.fill(rectangle2D);
        }

        int tempX = 0;
        int tempY = 0;

        // отрисовка точек и линий на графике
        for (int i = 1; i < y_axis.size() + 1; i += 1) {
            Ellipse2D ellipse2D1 = new Ellipse2D.Double(mar + i * (width - 2 * mar) / 7 - POINT_SIZE / 2, height - mar - POINT_SIZE / 2 - (((height - 2.5 * mar) / (double) getMax()) * y_axis.get(i - 1)), POINT_SIZE, POINT_SIZE);

            if (i != 1) {
                g.drawLine(tempX + POINT_SIZE / 2, tempY + POINT_SIZE / 2, (int) ellipse2D1.getX() + POINT_SIZE / 2, (int) ellipse2D1.getY() + POINT_SIZE / 2);
            }

            tempX = (int) ellipse2D1.getX();
            tempY = (int) ellipse2D1.getY();
            graphics2D.fill(ellipse2D1);
        }
    }

    // получить максимальную точку по оси oY
    private int getMax() {
        int m = 0;
        for (int item : y_axis) {
            if (item > m) {
                m = item;
            }

        }
        return m;
    }
}
