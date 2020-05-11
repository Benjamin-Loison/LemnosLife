import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;

public class Main
{
    public static ArrayList<String> getArrayListString(Map<String, ArrayList<String>> stringsWithKeys)
    {
        ArrayList<String> newStrings = new ArrayList<String>();
        Iterator<String> stringsWithKeysIterator = stringsWithKeys.keySet().iterator();
        while(stringsWithKeysIterator.hasNext())
        {
            String stringsWithKeysKey = stringsWithKeysIterator.next();
            newStrings.add(stringsWithKeysKey);
            newStrings.addAll(stringsWithKeys.get(stringsWithKeysKey));
        }
        return newStrings;
    }
    
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("."), files[] = currentFolder.listFiles();
        Map<String, ArrayList<String>> chunkLines = new HashMap<String, ArrayList<String>>();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".txt"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    ArrayList<String> lines = new ArrayList<String>();
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        lines.add(line);
                    }
                    scanner.close();
                    chunkLines.put(fName.replace(".txt", ""), lines);
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
        try
        {
            FileAPI.writeFile("roadsChunks.txt", getArrayListString(chunkLines));
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}