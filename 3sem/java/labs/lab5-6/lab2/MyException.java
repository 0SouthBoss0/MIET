package lab2;

public class MyException extends Exception {
    static int errorcounter = 0;

    public MyException() {
        super();
        errorcounter += 1;
    }

    public MyException(String message) {
        super(message);

    }

    public MyException(String message, Throwable cause) {
        super(message, cause);
        errorcounter += 1;
    }

    public MyException(Throwable cause) {
        super(cause);
        errorcounter += 1;
    }
}
