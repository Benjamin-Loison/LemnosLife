import java.io.File;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        Map<Character, Integer> biomesStats = new HashMap<Character, Integer>();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".biomes"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        for(int charIndex = 0; charIndex < line.length(); charIndex++)
                        {
                            char currentBiome = line.charAt(charIndex);
                            int biomesNumber = 1;
                            if(biomesStats.containsKey(currentBiome))
                            {
                                biomesNumber += biomesStats.get(currentBiome);
                            }
                            biomesStats.put(currentBiome, biomesNumber);
                        }
                    }
                    scanner.close();
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                }
            }
            else
            {
                Disp.print("Do not work on: " + fName);
            }
        }
        Iterator<Character> it = biomesStats.keySet().iterator();
        while(it.hasNext())
        {
            char currentBiome = it.next();
            Disp.print("Biome " + currentBiome + " is on the map " + biomesStats.get(currentBiome) + " times !");
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}