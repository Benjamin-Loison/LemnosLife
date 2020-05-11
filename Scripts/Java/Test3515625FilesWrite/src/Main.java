import java.io.File;
import java.io.FileWriter;

public class Main
{
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        try
        {
            for(int fileIndex = 0; fileIndex < 3515625; fileIndex++)
            {
                FileWriter fw = new FileWriter(new File("Test" + File.separator + fileIndex));
                for(int lineIndex = 0; lineIndex < 5; lineIndex++)
                    fw.write("XX XX XXX XXX XX\n");
                fw.close();
                System.out.println(fileIndex);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}