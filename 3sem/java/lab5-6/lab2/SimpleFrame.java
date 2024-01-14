package lab2;

import javax.swing.*;
import java.awt.*;


class SimpleFrame extends JFrame {
    int DEF_Width;
    int DEF_Height;

    public SimpleFrame(int width, int height) {
        DEF_Width = width;
        DEF_Height = height;
        setLayout(null);

        setSize(this.DEF_Width, this.DEF_Height);
        setResizable(false);
        Container c = getContentPane();

        // создание графиков
        GraphComponent gc11 = new GraphComponent(Main.arraylistadd);
        GraphComponent gc12 = new GraphComponent(Main.arraylistaddtotal);
        GraphComponent gc21 = new GraphComponent(Main.arraylistdelete);
        GraphComponent gc22 = new GraphComponent(Main.arraylistdeletetotal);
        GraphComponent gc31 = new GraphComponent(Main.linkedlistadd);
        GraphComponent gc32 = new GraphComponent(Main.linkedlistaddtotal);
        GraphComponent gc41 = new GraphComponent(Main.linkedlistdelete);
        GraphComponent gc42 = new GraphComponent(Main.linkedlistdeletetotal);

        // установка названий графикам
        gc11.setBorder(BorderFactory.createTitledBorder("ArrayList Add Median"));
        gc12.setBorder(BorderFactory.createTitledBorder("ArrayList Add Total"));
        gc21.setBorder(BorderFactory.createTitledBorder("ArrayList Remove Median"));
        gc22.setBorder(BorderFactory.createTitledBorder("ArrayList Remove Total"));
        gc31.setBorder(BorderFactory.createTitledBorder("LinkedList Add Median"));
        gc32.setBorder(BorderFactory.createTitledBorder("LinkedList Add Total"));
        gc41.setBorder(BorderFactory.createTitledBorder("LinkedList Remove Median"));
        gc42.setBorder(BorderFactory.createTitledBorder("LinkedList Remove Total"));

        // компоновка графиков на фрейме
        int h = getHeight() / 2 - 25;
        int w = getWidth() / 4 - 25;
        gc11.setBounds(0, 0, w, h);
        gc12.setBounds(w, 0, w, h);
        gc21.setBounds(2 * w, 0, w, h);
        gc22.setBounds(3 * w, 0, w, h);
        gc31.setBounds(0, h, w, h);
        gc32.setBounds(w, h, w, h);
        gc41.setBounds(2 * w, h, w, h);
        gc42.setBounds(3 * w, h, w, h);

        // добавление графиков в контейнер
        c.add(gc11);
        c.add(gc12);
        c.add(gc21);
        c.add(gc12);
        c.add(gc22);
        c.add(gc31);
        c.add(gc32);
        c.add(gc12);
        c.add(gc41);
        c.add(gc42);
    }
}