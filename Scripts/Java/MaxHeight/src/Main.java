import java.io.File;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args) // Altis: 349.13
    {
        Time.initializeTimer();
        File currentFolder = new File("ground");
        File[] files = currentFolder.listFiles();
        double maxHeight = -1000;
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
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        String[] parts = line.split(" ");
                        for(int partsIndex = 0; partsIndex < parts.length; partsIndex++)
                        {
                            String part = parts[partsIndex];
                            if(part.equals("N"))
                                continue;
                            else
                            {
                                Double altitude = Double.parseDouble(part);
                                if(altitude > maxHeight)
                                {
                                    maxHeight = altitude;
                                }
                            }
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
        Disp.print(maxHeight);
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}