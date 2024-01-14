package lab2;

import javax.swing.*;
import java.awt.*;

public class RaceComponent extends JPanel {
    int mar = 0;
    public int squaresize = 20;

    public void paintComponent(Graphics g) {

        super.paintComponent(g);
        Graphics2D graphics2D = (Graphics2D) g;
        g.setFont(new Font("TimesRoman", Font.PLAIN, 10));
        drawFinishLine(graphics2D);
    }


    public void drawFinishLine(Graphics2D graphics2D) {
        for (int i = 0; i < 4; i++) {
            int counter = 0;
            while (counter < getHeight()) {
                Rectangle rectangle = new Rectangle(squaresize, squaresize);

                if ((i + counter) % 2 == 0) {
                    graphics2D.setColor(Color.black);
                } else {
                    graphics2D.setColor(Color.WHITE);
                }
                rectangle.setBounds(getWidth() - i * squaresize, counter * squaresize, squaresize, squaresize);
                graphics2D.fill(rectangle);
                counter += 1;
            }
        }
    }
}
