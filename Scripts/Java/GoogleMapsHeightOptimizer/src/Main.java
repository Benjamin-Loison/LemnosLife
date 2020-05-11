import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    private static final String BOTTOM_WATER_FOR_AC_STR = "-100";
    private static final double BOTTOM_WATER_FOR_AC = Double.parseDouble(BOTTOM_WATER_FOR_AC_STR);

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
                    ArrayList<String> newLines = new ArrayList<String>();
                    Scanner scanner = new Scanner(file);
                    boolean isUsefullChunk = false;
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine(), newLine = "";
                        String[] parts = line.split(" ");
                        int partsLength = parts.length;
                        for(int partIndex = 0; partIndex < partsLength; partIndex++)
                        {
                            String part = parts[partIndex];
                            if(part.contains("E") || part.equals("-"))
                                part = "0";
                            double height = Double.parseDouble(part);
                            if(height > BOTTOM_WATER_FOR_AC /*&& height != 0*/)
                            {
                                isUsefullChunk = true;
                            }
                            else
                            {
                                height = BOTTOM_WATER_FOR_AC;
                            }
                            newLine += (height + " ").replace(".0 ", " ").replace(" ", "");
                            if(partIndex != partsLength - 1)
                            {
                                newLine += " ";
                            }
                        }
                        newLines.add(newLine.replaceAll(BOTTOM_WATER_FOR_AC_STR, "N"));
                    }
                    scanner.close();
                    file.delete();
                    if(isUsefullChunk)
                    {
                        FileWriter fw = new FileWriter(file);
                        int newLinesSize = newLines.size();
                        for(int newLinesIndex = 0; newLinesIndex < newLinesSize; newLinesIndex++)
                        {
                            fw.write(newLines.get(newLinesIndex));
                            if(newLinesIndex != newLinesSize - 1)
                            {
                                fw.write("\n");
                            }
                        }
                        fw.close();
                    }
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