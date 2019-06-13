import java.io.File;
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
            if(fName.endsWith(".height"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scanner = new Scanner(file);
                    int linesNumber = 0;
                    int elementsEachLine = 0;
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        linesNumber++;
                        String[] parts = line.split(" ");
                        elementsEachLine = parts.length;
                        Disp.print(elementsEachLine);
                    }
                    Disp.print(linesNumber + " " + elementsEachLine);
                    scanner.close();
                }
                catch(Exception e)
                {
                    e.printStackTrace();
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