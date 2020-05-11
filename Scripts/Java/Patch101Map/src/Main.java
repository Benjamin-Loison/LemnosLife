import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;

public class Main
{    
    static final String HEIGHT_EXTENSION = ".height";

    public static void main(String[] args) // TODO: direct patch in treatment from extracted data
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        HashMap<String, ArrayList<String>> mapData = new HashMap<String, ArrayList<String>>();
        ArrayList<String> filesName = new ArrayList<String>();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(HEIGHT_EXTENSION))
            {
                Disp.print("Working on: " + fName);
                String chunk = fName.replace(HEIGHT_EXTENSION, "");
                filesName.add(chunk);
                try
                {
                    ArrayList<String> lines = new ArrayList<String>();
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine(); // take value from next file otherwise repeat and make algo modular
                        lines.add(line);
                    }
                    scanner.close();
                    mapData.put(chunk, lines);
                    file.delete();
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
            Iterator<String> mapDataKeysIt = mapData.keySet().iterator();
            while(mapDataKeysIt.hasNext())
            {
                String key = mapDataKeysIt.next();
                ArrayList<String> lines = mapData.get(key);

                // treatment
                String nextRightChk = getNextRightChk(key);
                boolean nextRightExists = filesName.contains(nextRightChk);

                String nextBottomChk = getNextBottomChk(key);
                boolean nextBottomExists = filesName.contains(nextBottomChk);

                String nextBottomRightChk = getNextRightChk(nextBottomChk);
                boolean nextBottomRightExists = filesName.contains(nextBottomRightChk);

                Disp.printAndLog(key);
                Disp.printAndLog(nextRightChk + " " + nextRightExists);
                Disp.printAndLog(nextBottomChk + " " + nextBottomExists);
                Disp.printAndLog(nextBottomRightChk + " " + nextBottomRightExists);
                
                // right treatment
                if(nextRightExists) // take data from right
                {
                    int linesSize = lines.size();
                    for(int linesIndex = 0; linesIndex < linesSize; linesIndex++)
                    {
                        lines.set(linesIndex, lines.get(linesIndex) + " " + getFirstPart(mapData.get(nextRightChk).get(linesIndex)));
                    }
                }
                else // repeat last data
                {
                    int linesSize = lines.size();
                    for(int linesIndex = 0; linesIndex < linesSize; linesIndex++)
                    {
                        String line = lines.get(linesIndex);
                        lines.set(linesIndex, line + " " + getLastPart(line));
                    }
                }

                // bottom treatment
                if(nextBottomExists) // take data from bottom
                {
                    if(nextBottomRightExists) // and data from bottom right
                    {
                        String nextBottomLine = mapData.get(nextBottomChk).get(0);
                        String nextBottomRightPart = getFirstPart(mapData.get(nextBottomRightChk).get(0));
                        lines.add(nextBottomLine + " " + nextBottomRightPart);
                    }
                    else // and repeat last bottom last element data
                    {
                        String nextBottomLine = mapData.get(nextBottomChk).get(0);
                        lines.add(nextBottomLine + " " + getLastPart(nextBottomLine));
                    }
                }
                else // repeat bottom (treated)
                {
                    lines.add(lines.get(lines.size() - 1));
                }

                // write
                File file = new File(key + HEIGHT_EXTENSION);
                FileWriter fw = new FileWriter(file);
                int linesSize = lines.size();
                for(int linesIndex = 0; linesIndex < linesSize; linesIndex++)
                {
                    fw.write(lines.get(linesIndex));
                    if(linesIndex != linesSize - 1)
                        fw.write("\n");
                }
                fw.close();
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }

    static int[] getNbFromChk(String chkName)
    {
        int[] chunkXY = new int[2];
        String[] parts = chkName.split(" ");
        for(short partsIndex = 0; partsIndex < parts.length; partsIndex++)
            chunkXY[partsIndex] = Integer.parseInt(parts[partsIndex]);
        return chunkXY;
    }

    static String getNextRightChk(String chkName)
    {
        int[] chunkXY = getNbFromChk(chkName);
        return (chunkXY[0] + 1) + " " + chunkXY[1];
    }

    static String getNextBottomChk(String chkName)
    {
        int[] chunkXY = getNbFromChk(chkName);
        return chunkXY[0] + " " + (chunkXY[1] - 1);
    }
    
    static String getFirstPart(String line)
    {
        return line.split(" ")[0];
    }
    
    static String getLastPart(String line)
    {
        String[] parts = line.split(" ");
        return parts[parts.length - 1];
    }
}