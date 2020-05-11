import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("."), files[] = currentFolder.listFiles();
        try
        {
            FileWriter fw = new FileWriter(new File("modelsPath.txt"));
            ArrayList<String> paths = new ArrayList<String>();
            for(int i = 0; i < files.length; i++)
            {
                File file = files[i];
                String fName = file.getName();
                if(fName.endsWith(".rpt"))
                {
                    Disp.print("Working on: " + fName);
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        if(line.contains(" Model: "))
                        {
                            String path = line.split("\"\"")[1].replace("\"", "");
                            if(!paths.contains(path))
                            {
                                paths.add(path);
                                fw.write(path + "\n");
                            }
                        }
                    }
                    scanner.close();
                }
                else
                {
                    Disp.print("Do not work on: " + fName);
                }
            }
            fw.close();
        }
        catch(Exception exception)
        {
            exception.printStackTrace();
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}