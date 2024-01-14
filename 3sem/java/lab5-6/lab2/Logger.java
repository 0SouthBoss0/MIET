package lab2;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Time;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class Logger {
    String filename;
    String endlog;

    public Logger(String filename, boolean rewrite) {
        this.filename = filename;
        endlog = "";
        if (rewrite) {
            File file = new File(filename);
            if (file.exists()) {
                boolean success = file.delete();
            }
        }
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

    public void createTimeLog(String type, String key, int index, long time) {
        try {
            FileWriter writer = new FileWriter(filename, true);
            writer.write(type + ", " + key + " = " + index + ", " + time + "\n");
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void saveEndLog() {
        try {
            FileWriter writer = new FileWriter(filename, true);
            writer.write("\nRESULT MAIN LOGS:\n" + endlog);
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void addEndLog(String message) {
        endlog += "\n" + message + "\n";
    }

}
