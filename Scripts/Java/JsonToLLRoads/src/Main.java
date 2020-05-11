import java.io.File;
import java.io.FileWriter;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("."), files[] = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".json"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scanner = new Scanner(file);
                    ArrayList<String> lines = new ArrayList<String>();
                    //int lineIndex = 0;
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine(), newLine = "";
                        String[] lineParts = line.split("@");
                        String[] lineParts0Parts = lineParts[0].split(" ");
                        int lineParts0PartsLength = lineParts0Parts.length;
                        DecimalFormat df = new DecimalFormat("####0.00");
                        for(int lineParts0PartsIndex = 0; lineParts0PartsIndex < lineParts0PartsLength; lineParts0PartsIndex++)
                        {
                            String[] lineParts0PartsIndexParts = lineParts0Parts[lineParts0PartsIndex].split(",");
                            newLine += df.format(Double.parseDouble(lineParts0PartsIndexParts[0]) - 200000) + "," + df.format(Double.parseDouble(lineParts0PartsIndexParts[1]));
                            if(lineParts0PartsIndex < lineParts0PartsLength - 1)
                                newLine += " ";
                        }
                        //Disp.print(lineIndex);
                        newLine += "@" + lineParts[1];
                        lines.add(newLine);
                        //lineIndex++;
                    }
                    scanner.close();
                    file.delete();
                    FileWriter fw = new FileWriter(file);
                    int linesSize = lines.size();
                    for(int linesIndex = 0; linesIndex < linesSize; linesIndex++)
                    {
                        fw.write(lines.get(linesIndex));
                        if(linesIndex < linesSize - 1)
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