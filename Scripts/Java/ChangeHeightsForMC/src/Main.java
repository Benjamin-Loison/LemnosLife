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
        File currentFolder = new File("ground"), files[] = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".height"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    ArrayList<String> lines = new ArrayList<String>();
                    Scanner scanner = new Scanner(file);
                    int linePartsLength = -1;
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine(), newLine = "", lineParts[] = line.split(" ");
                        linePartsLength = lineParts.length;
                        for(int linePartsIndex = 0; linePartsIndex < linePartsLength; linePartsIndex++)
                        {
                            String linePart = lineParts[linePartsIndex];
                            short value = -1;
                            if(linePart.equals("N"))
                                value = 0;
                            else
                            {
                                double height = Double.parseDouble(linePart);
                                value = (short)Math.round((height + 100) * (255.0 / 449.13)); // heighest altitude + positive deepest (negative) altitude
                            }
                            newLine += value;
                            if(linePartsIndex < linePartsLength - 1)
                                newLine += " ";
                        }
                        lines.add(newLine);
                    }
                    scanner.close();
                    file.delete();
                    FileWriter fw = new FileWriter(file);
                    for(int lineIndex = 0; lineIndex < linePartsLength; lineIndex++)
                    {
                        fw.write(lines.get(lineIndex));
                        if(lineIndex < linePartsLength - 1)
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
        Disp.closeLogger();
    }
}