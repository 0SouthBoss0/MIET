package lab2;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class Logger {
    String filename;

    public Logger(String filename) {
        this.filename = filename;
    }

    // добавить строку лога
    public void createLog(String message) {
        LocalTime time = LocalTime.now();
        try {
            FileWriter writer = new FileWriter(filename, true);
            BufferedWriter bufferWriter = new BufferedWriter(writer);
            bufferWriter.write(time.format(DateTimeFormatter.ofPattern("H:mm:ss:SS")) + "\t" + message + "\n");
            bufferWriter.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
