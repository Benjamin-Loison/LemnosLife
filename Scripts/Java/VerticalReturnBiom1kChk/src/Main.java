import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
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
            if(fName.endsWith(".biomes"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scanner = new Scanner(file);
                    ArrayList<String> lines = new ArrayList<String>();
                    while(scanner.hasNextLine())
                    {
                        lines.add(scanner.nextLine());
                    }
                    scanner.close();
                    file.delete();
                    FileWriter fw = new FileWriter(file);
                    for(int lineIndex = lines.size() - 1; lineIndex >= 0; lineIndex--)
                    {
                        fw.write(lines.get(lineIndex));
                        if(lineIndex != 0)
                            fw.write("\n");
                    }
                    fw.close();
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