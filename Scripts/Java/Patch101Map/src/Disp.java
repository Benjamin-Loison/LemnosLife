import java.io.File;
import java.io.FileWriter;

public class Disp
{
    static File logFile = new File("log.txt");
    static FileWriter fw;

    public static void initializeLogger()
    {
        try
        {
            fw = new FileWriter(logFile);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    private static String getLogString(Object obj)
    {
        return Time.getTimeFormatted() + " " + obj.toString();
    }
    
    public static void printAndLog(Object obj)
    {
        log(obj);
        print(obj);
    }

    public static void log(Object obj)
    {
        try
        {
            fw.write(getLogString(obj) + "\n");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    public static void print(Object obj)
    {
        System.out.println(getLogString(obj));
    }
}