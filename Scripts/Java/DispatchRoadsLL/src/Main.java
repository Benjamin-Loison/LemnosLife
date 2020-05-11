import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;

public class Main
{
    private static final int CHUNK_SIZE = 1000;

    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        Map<String, ArrayList<Integer>> roads = new HashMap<String, ArrayList<Integer>>();
        File file = new File("roads.txt");
        try
        {
            Scanner scanner = new Scanner(file);
            int lineIndex = 0;
            while(scanner.hasNextLine())
            {
                String line = scanner.nextLine();
                String[] lineParts = line.split("@");
                String[] lineParts0Parts = lineParts[0].split(" ");
                for(int lineParts0PartsIndex = 0; lineParts0PartsIndex < lineParts0Parts.length; lineParts0PartsIndex++)
                {
                    String[] lineParts0PartsIndexParts = lineParts0Parts[lineParts0PartsIndex].split(",");
                    int x = (int)Math.round(Double.parseDouble(lineParts0PartsIndexParts[0])), y = (int)Math.round(Double.parseDouble(lineParts0PartsIndexParts[1]));
                    String chunkName = (x - (x % CHUNK_SIZE)) / CHUNK_SIZE + " " + (y - (y % CHUNK_SIZE)) / CHUNK_SIZE;
                    ArrayList<Integer> chunksId = roads.get(chunkName);
                    if(chunksId == null)
                    {
                        ArrayList<Integer> newIds = new ArrayList<Integer>();
                        newIds.add(lineIndex);
                        roads.put(chunkName, newIds);
                    }
                    else
                    {
                        if(!chunksId.contains(lineIndex))
                        {
                            chunksId.add(lineIndex);
                            roads.put(chunkName, chunksId);
                        }
                    }
                }
                lineIndex++;
            }
            scanner.close();
            Iterator<String> roadsIterator = roads.keySet().iterator();
            while(roadsIterator.hasNext())
            {
                String roadsKey = roadsIterator.next();
                FileAPI.writeFile(roadsKey + ".txt", ArrayListAPI.getArrayListString(roads.get(roadsKey)));
            }
        }
        catch(Exception exception)
        {
            exception.printStackTrace();
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}