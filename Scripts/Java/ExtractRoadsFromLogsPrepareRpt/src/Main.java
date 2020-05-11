import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File newFile = new File("input.rpt");
        try
        {
            FileWriter fw = new FileWriter(newFile);
            File file = new File("Arma3_x64_2019-04-26_21-10-52.rpt");
            String fName = file.getName();
            if(fName.endsWith(".rpt"))
            {
                Disp.print("Working on: " + fName);
                Scanner scanner = new Scanner(file);
                while(scanner.hasNextLine())
                {
                    String line = scanner.nextLine();
                    line = line.split("\"")[1];
                    String[] lineParts = line.split(" ");

                    lineParts[0] = lineParts[0].substring(0, lineParts[0].length() - 2);
                    lineParts[1] = lineParts[1].substring(0, lineParts[1].length() - 2);
                    fw.write(lineParts[0] + " " + lineParts[1]);
                    if(scanner.hasNextLine())
                        fw.write("\n");
                }
                scanner.close();
            }
            else
            {
                Disp.print("Do not work on: " + fName);
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