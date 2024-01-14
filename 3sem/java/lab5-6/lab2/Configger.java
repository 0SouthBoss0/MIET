package lab2;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

public class Configger {
    Properties properties;
    String filename;

    public Configger(String filename) {
        properties = new Properties();
        this.filename = filename;
    }

    // получить значение из файла конфигурации
    public String get(String key) {
        try (FileInputStream fis = new FileInputStream(filename)) {
            properties.load(fis);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return String.valueOf(properties.get(key));
    }

    // установить значение в файле конфигурации
    public void set(String key, String value) {
        properties.setProperty(key, value);
    }

    // сохранить файл конфигурации
    public void save() throws IOException {
        FileOutputStream out = new FileOutputStream(filename);
        properties.store(out, null);
        out.close();

    }
}
