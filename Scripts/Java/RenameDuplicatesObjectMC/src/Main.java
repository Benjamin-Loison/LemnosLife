import java.io.File;
import java.io.FileWriter;
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
        File changeFile = new File("change.txt");
        Disp.print("Reading change...");
        try
        {
            Scanner scanner = new Scanner(changeFile);
            Map<Integer, ArrayList<Integer>> change = new HashMap<Integer, ArrayList<Integer>>();
            while(scanner.hasNextLine())
            {
                String line = scanner.nextLine();
                String[] lineParts = line.split(" ");
                int id = Integer.parseInt(lineParts[0]);
                ArrayList<Integer> ids = new ArrayList<Integer>();
                for(int linePartsIndex = 1; linePartsIndex < lineParts.length; linePartsIndex++)
                {
                    ids.add(Integer.parseInt(lineParts[linePartsIndex]));
                }
                change.put(id, ids);
            }
            scanner.close();
            Disp.print("Change read !");
            File currentFolder = new File("."), files[] = currentFolder.listFiles();
            for(int i = 0; i < files.length; i++)
            {
                File file = files[i];
                String fName = file.getName();
                if(fName.endsWith(".objects"))
                {
                    Disp.print("Working on: " + fName);
                    scanner = new Scanner(file);
                    ArrayList<String> newLines = new ArrayList<String>();
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        String[] lineParts = line.split(" ");
                        int linePartsLength = lineParts.length;
                        if(linePartsLength == 5)
                        {
                            int id = Integer.parseInt(lineParts[0]);
                            Iterator<Integer> changeKeys = change.keySet().iterator();
                            while(changeKeys.hasNext())
                            {
                                int key = changeKeys.next();
                                if(change.get(key).contains(id))
                                {
                                    id = key;
                                    break;
                                }
                            }
                            String newLine = id + " ";
                            for(int linePartsIndex = 1; linePartsIndex < linePartsLength; linePartsIndex++)
                            {
                                newLine += lineParts[linePartsIndex];
                                if(linePartsIndex < linePartsLength - 1)
                                {
                                    newLine += " ";
                                }
                            }
                            newLines.add(newLine);
                        }
                        else
                            newLines.add(line);
                    }
                    scanner.close();
                    file.delete();
                    FileWriter fw = new FileWriter(file);
                    int newLinesSize = newLines.size();
                    for(int newLinesIndex = 0; newLinesIndex < newLinesSize; newLinesIndex++)
                    {
                        fw.write(newLines.get(newLinesIndex));
                        if(newLinesIndex < newLinesSize - 1)
                            fw.write("\n");
                    }
                    fw.close();
                }
                else
                    Disp.print("Do not work on: " + fName);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}