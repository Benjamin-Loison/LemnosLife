import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".key"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    boolean needReturnLine = false;
                    FileWriter fw = new FileWriter(new File("clean.txt"));
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        if(line.equals("") || line.contains("x"))
                            continue;
                        if(needReturnLine)
                            fw.write(" " + line + "\n");
                        else
                            fw.write(line);
                        needReturnLine = !needReturnLine;
                    }
                    scanner.close();
                    fw.close();
                }
                catch(Exception exception)
                {
                    exception.printStackTrace();
                }
            }
            else
            {
                Disp.print("Do not work on: " + fName);
            }
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}