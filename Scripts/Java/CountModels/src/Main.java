import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("objects"), files[] = currentFolder.listFiles();
        ArrayList<Integer> models = new ArrayList<Integer>();
        for(int i = 0; i < 100000; i++)
        {
            models.add(0);
        }
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".objects"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        String[] lineParts = line.split(" ");
                        if(lineParts.length != 2)
                        {
                            int id = Integer.parseInt(lineParts[0]);
                            /*if(models.contains(id))*/
                            {
                                models.set(id, models.get(id) + 1);
                               // Disp.print("h");
                            }
                            /*else
                            {
                                models.set(id, 1);
                                
                            }*/
                        }
                    }
                    scanner.close();
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
        for(int i = 0; i < models.size(); i++)
        {
            if(models.get(i) != 0)
            {
                System.out.println(models.get(i) + "," + i);
            }
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}