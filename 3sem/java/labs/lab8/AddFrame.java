package lab2;

import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AddFrame extends JFrame {
    public AddFrame() {
        final JFrame frame = new JFrame("Лабораторная 8");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        frame.setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));
        frame.add(new JLabel("Адрес электронной почты"));

        JTextFieldWithHint email = new JTextFieldWithHint("email");
        email.setPreferredSize(new Dimension(200, 30));
        frame.add(email);
        frame.add(new JLabel("Тема письма"));

        JTextFieldWithHint subject = new JTextFieldWithHint("subject");
        subject.setPreferredSize(new Dimension(200, 30));
        frame.add(subject);

        frame.add(new JLabel("Содержание письма"));

        JTextFieldWithHint message = new JTextFieldWithHint("message");
        message.setPreferredSize(new Dimension(200, 30));
        frame.add(message);

        JLabel info = new JLabel("");
        frame.add(info);

        JButton sendbutton = new JButton("Отправить");
        frame.add(sendbutton);
        Component[] components = {email, subject, message};


        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                // Открытие окна
                frame.pack();
                frame.setVisible(true);

            }
        });

        sendbutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String field_address = email.getText();
                String field_subject = subject.getText();
                String field_message = message.getText();
                if (isValidEmailAddress(field_address)) {
                    MailTest.send(field_address, field_subject, field_message);
                    info.setText("Успешно отправлено!");
                    info.setForeground(Color.BLACK);
                } else {
                    info.setText("Ошибка!");
                    info.setForeground(Color.RED);
                    // очистка полей ввода и установка подсказок
                    for (Component component : components) {
                        ((JTextFieldWithHint) component).setText(((JTextFieldWithHint) component).hint);
                        component.setFont(((JTextFieldWithHint) component).gainFont);
                        component.setForeground(Color.GRAY);

                    }
                }


            }
        });
    }

    public static boolean isValidEmailAddress(String email) {
        boolean result = true;
        try {
            InternetAddress emailAddr = new InternetAddress(email);
            emailAddr.validate();
        } catch (AddressException ex) {
            result = false;
        }
        return result;
    }
}



