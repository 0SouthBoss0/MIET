package lab2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;

public class AddFrame extends JFrame {
    private static JPanel cards;


    public AddFrame() {
        final JFrame frame = new JFrame("Лабораторная 6");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createPanelUI(frame.getContentPane());

                // Открытие окна
                frame.pack();
                frame.setVisible(true);

            }
        });
    }

    public void createPanelUI(Container container) {
        // выпадающий список
        JComboBox<String> combobox = new JComboBox<>(new String[]{"Добавление Car", "Добавление Truck", "Добавление PolicePoint"});
        combobox.setEditable(false);
        combobox.addItemListener(this::itemStateChanged);

        // заголовок
        JPanel cbPanel = new JPanel();
        cbPanel.setLayout(new BoxLayout(cbPanel, BoxLayout.Y_AXIS));
        JLabel title = new JLabel("Добавление нового объекта");
        title.setAlignmentX(Component.CENTER_ALIGNMENT);
        cbPanel.add(title);
        cbPanel.add(combobox);

        // панель добавления машины
        JPanel card1 = new JPanel();
        card1.add(new JTextFieldWithHint("Модель "));
        card1.add(new JTextFieldWithHint("Максимальная скорость "));
        card1.add(new JTextFieldWithHint("Радиостанция "));

        // панель добавления грузовика
        JPanel card2 = new JPanel();
        card2.add(new JTextFieldWithHint("Модель "));
        card2.add(new JTextFieldWithHint("Максимальная скорость "));
        card2.add(new JTextFieldWithHint("Радиостанция "));
        card2.add(new JTextFieldWithHint("Вес "));
        card2.add(new JTextFieldWithHint("Высота "));

        // панель добавления пункта ДПС
        JPanel card3 = new JPanel();
        card3.add(new JTextFieldWithHint("Ограничение скорости "));
        card3.add(new JTextFieldWithHint("Ограничение веса "));
        card3.add(new JTextFieldWithHint("Ограничение высоты "));

        // панель с менеджером расположения CardLayout
        cards = new JPanel(new CardLayout());
        cards.add(card1, "Добавление Car");
        cards.add(card2, "Добавление Truck");
        cards.add(card3, "Добавление PolicePoint");

        // кнопка сохранения
        JButton button = new JButton("Сохранить");
        button.setAlignmentX(Component.CENTER_ALIGNMENT);
        button.setBackground(Color.GREEN);
        JPanel press = new JPanel();
        press.setLayout(new BoxLayout(press, BoxLayout.Y_AXIS));
        press.add(button);

        // надпись ошибки ввода
        JPanel errorPanel = new JPanel();
        errorPanel.setLayout(new BoxLayout(errorPanel, BoxLayout.Y_AXIS));
        JLabel error = new JLabel("Нажмите кнопку для сохранения объекта");
        error.setAlignmentX(Component.CENTER_ALIGNMENT);
        errorPanel.add(error);

        // добавление панелей в контейнер
        container.setLayout(new BoxLayout(container, BoxLayout.Y_AXIS));
        container.add(cbPanel);
        container.add(cards);
        container.add(errorPanel);
        container.add(press);


        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                switch (combobox.getSelectedIndex()) {
                    case 0 -> {
                        Component[] components = card1.getComponents();
                        try {
                            int maxspeed = Integer.parseInt(((JTextFieldWithHint) components[1]).getText());
                            if (maxspeed > 300 || maxspeed < 0) {
                                throw new Exception();
                            }
                            Car newcar = new Car(((JTextFieldWithHint) components[0]).getText(), maxspeed, new Radio(((JTextFieldWithHint) components[2]).getText(), true));
                            Main.objectslist.myobjects.add(newcar);
                            error.setText("Объект успешно сохранён!");
                            error.setForeground(Color.BLACK);
                        } catch (Exception exception) {
                            error.setText("Ошибка ввода!");
                            error.setForeground(Color.RED);

                        }
                        // очистка полей ввода и установка подсказок
                        for (Component component : components) {
                            ((JTextFieldWithHint) component).setText(((JTextFieldWithHint) component).hint);
                            component.setFont(((JTextFieldWithHint) component).gainFont);
                            component.setForeground(Color.GRAY);
                        }
                    }
                    case 1 -> {
                        Component[] components2 = card2.getComponents();
                        try {
                            int maxspeed = Integer.parseInt(((JTextFieldWithHint) components2[1]).getText());
                            int weight = Integer.parseInt(((JTextFieldWithHint) components2[3]).getText());
                            int height = Integer.parseInt(((JTextFieldWithHint) components2[4]).getText());
                            if (maxspeed > 200 || maxspeed < 0 || weight > 10000 || weight < 0 || height > 500 || height < 0) {
                                throw new Exception();
                            }
                            Truck newtruck = new Truck(((JTextFieldWithHint) components2[0]).getText(), maxspeed, new Radio(((JTextFieldWithHint) components2[2]).getText(), true), weight, height);
                            Main.objectslist.myobjects.add(newtruck);
                            error.setText("Объект успешно сохранён!");
                            error.setForeground(Color.BLACK);
                        } catch (Exception exception) {
                            error.setText("Ошибка ввода!");
                            error.setForeground(Color.RED);

                        }
                        // очистка полей ввода и установка подсказок
                        for (Component component : components2) {
                            ((JTextFieldWithHint) component).setText(((JTextFieldWithHint) component).hint);
                            component.setFont(((JTextFieldWithHint) component).gainFont);
                            component.setForeground(Color.GRAY);
                        }
                    }
                    case 2 -> {
                        Component[] components3 = card3.getComponents();
                        try {
                            int maxspeed = Integer.parseInt(((JTextFieldWithHint) components3[0]).getText());
                            int maxweight = Integer.parseInt(((JTextFieldWithHint) components3[1]).getText());
                            int maxheight = Integer.parseInt(((JTextFieldWithHint) components3[2]).getText());
                            if (maxspeed < 0 || maxweight < 0 || maxheight < 0) {
                                throw new Exception();
                            }
                            PolicePoint newpolicepoint = new PolicePoint(maxspeed, maxweight, maxheight);
                            Main.objectslist.myobjects.add(newpolicepoint);
                            error.setText("Объект успешно сохранён!");
                            error.setForeground(Color.BLACK);
                        } catch (Exception exception) {
                            error.setText("Ошибка ввода!");
                            error.setForeground(Color.RED);

                        }
                        // очистка полей ввода и установка подсказок
                        for (Component component : components3) {
                            ((JTextFieldWithHint) component).setText(((JTextFieldWithHint) component).hint);
                            component.setFont(((JTextFieldWithHint) component).gainFont);
                            component.setForeground(Color.GRAY);
                        }
                    }
                }

            }
        });
    }

    public void itemStateChanged(ItemEvent event) {
        CardLayout layout = (CardLayout) (cards.getLayout());
        layout.show(cards, (String) event.getItem());
    }

}
