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
        File currentFolder = new File("."), files[] = currentFolder.listFiles();
        Map<String, ArrayList<String>> biomes = new HashMap<String, ArrayList<String>>();
        try
        {
            ArrayList<String> empty = new ArrayList<String>();
            for(int i = 0; i < files.length; i++)
            {
                File file = files[i];
                String fName = file.getName();
                if(fName.endsWith(".biomes"))
                {
                    //Disp.print("Working on: " + fName);
                    Scanner scanner = new Scanner(file);
                    ArrayList<String> lines = new ArrayList<String>();
                    while(scanner.hasNextLine())
                        lines.add(scanner.nextLine());
                    biomes.put(fName.replace(".biomes", ""), lines);
                    scanner.close();
                    file.delete();
                }
                else
                {
                    Disp.print("Do not work on: " + fName);
                }
            }
            String emptyLine = "";
            for(int i = 0; i < 126; i++)
                emptyLine += "6";
            for(int i = 0; i < 126; i++)
                empty.add(emptyLine);

            Disp.print("Work on rpt file now..."); // replace in biomes
            File rptFile = new File("input.rpt");
            Scanner scanner = new Scanner(rptFile);
            while(scanner.hasNextLine()) // let's assume that where roads are, biomes are (don't check if biomes chunk exists) - AND NOPE x)
            {
                String line = scanner.nextLine();
                //line = line.split("\"")[1];
                String[] lineParts = line.split(" ");

                //lineParts[0] = lineParts[0].substring(0, lineParts[0].length() - 2);
                //lineParts[1] = lineParts[1].substring(0, lineParts[1].length() - 2);

                int x = Integer.parseInt(lineParts[0]), y = Integer.parseInt(lineParts[1]);
                int reminderXInChk = x % 1000, reminderYInChk = y % 1000;
                String chkName = (x / 1000) + " " + (y / 1000);
                ArrayList<String> lines = biomes.get(chkName);
                if(lines == null)
                    lines = empty;
                int newY = (reminderYInChk - (reminderYInChk % 8)) / 8;
                String newLine = lines.get(newY); // may need to be replaced because biomes are not well oriented
                int column = (reminderXInChk - (reminderXInChk % 8)) / 8;

                //Disp.print(newY);
                lines.set(newY, newLine.substring(0, column) + 'J' + newLine.substring(column + 1)); /// not x
                biomes.put(chkName, lines);
            }
            scanner.close();
        }
        catch(Exception exception)
        {
            exception.printStackTrace();
        }

        Iterator<String> keys = biomes.keySet().iterator(); /// rewrite all biomes
        while(keys.hasNext())
        {
            String key = keys.next();
            //Disp.print("Writing biome: " + key);
            ArrayList<String> lines = biomes.get(key);
            try
            {
                FileWriter fw = new FileWriter(new File(key + ".biomes"));
                int linesSize = lines.size();
                for(int lineIndex = 0; lineIndex < linesSize; lineIndex++)
                {
                    fw.write(lines.get(lineIndex));
                    if(lineIndex < linesSize - 1)
                        fw.write("\n");
                }
                fw.close();
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
        }

        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}