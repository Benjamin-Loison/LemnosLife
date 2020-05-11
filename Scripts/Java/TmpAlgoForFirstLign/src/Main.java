import java.io.File;
import java.io.FileNotFoundException;
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
            if(fName.endsWith(".block"))
            {
                try
                {
                    Disp.print("Working on: " + fName);
                    Scanner scan = new Scanner(file);
                    boolean usefull = false;
                    while(scan.hasNextLine())
                    {
                        String line = scan.nextLine();
                        String[] parts = line.split("@");
                        for(int j = 0; j < parts.length; j++)
                        {
                            String part = parts[j];
                            if(!part.equals("-185.97#7") && !part.equals("-185") & !part.equals("-1"))
                            {
                                Disp.print("!" + part + "!");
                                usefull = true;
                            }
                        }
                    }
                    scan.close();
                    if(usefull)
                    {
                        Disp.print("File: " + fName + " has usefull info, conservating...");
                    }
                    else
                    {
                        Disp.print("File: " + fName + " hasn't usefull info, deleting...");
                        file.delete();
                    }
                }
                catch(FileNotFoundException e)
                {
                    e.printStackTrace();
                }
            }
            else
                System.out.println("Don't work on: " + fName);
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}