import java.io.File;
import java.io.FileWriter;

public class Disp
{
    static FileWriter fw;

    public static void initializeLogger()
    {
        try
        {
            fw = new FileWriter(new File("logs.txt"));
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    public static void print(Object obj)
    {
        String logStr = Time.getTimeFormatted() + " " + obj.toString();
        System.out.println(logStr);
        try
        {
            fw.write(logStr + "\n");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    public static void closeLogger()
    {
        try
        {
            fw.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
}