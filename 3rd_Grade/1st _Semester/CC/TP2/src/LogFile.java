import java.io.File;
import java.io.IOException;
import java.util.logging.*;

public class LogFile {
    public Logger logger;
    FileHandler handler;

    //Constructor
    public LogFile(String filename) throws SecurityException, IOException {
        File file = new File(filename);
        if (!file.exists()) {
            boolean newFile = file.createNewFile();
        }

        //handler & format
        handler = new FileHandler(filename, true);
        //format in logfile
        handler.setFormatter(new Formatter() {
            public String format(LogRecord rec) {
                StringBuffer buf = new StringBuffer(1000);
                buf.append(new java.util.Date());
                buf.append(' ');
                buf.append(rec.getLevel());
                buf.append(' ');
                buf.append(formatMessage(rec));
                buf.append('\n');
                return buf.toString();
            }
        });
        //add handler to logger
        logger = Logger.getLogger("test");
        logger.addHandler(handler);
    }
}
