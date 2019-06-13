import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Time.initializeTimer();
        String FOLDER = "height", EXTENSION = "height";
        File currentFolder = new File(FOLDER);
        File[] files = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith("." + EXTENSION))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    ArrayList<String> lines = new ArrayList<String>();
                    
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        lines.add(line);
                    }
                    scanner.close();
                    
                    file.delete();
                    
                    FileWriter fw = new FileWriter(file);
                    int linesSize = lines.size();
                    for(int linesIndex = linesSize - 1; linesIndex >= 0; linesIndex--)
                    {
                        fw.write(lines.get(linesIndex));
                        if(linesIndex != 0)
                            fw.write("\n");
                    }
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