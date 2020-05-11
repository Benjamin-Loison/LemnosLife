import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    static final char GRASS_GREEN = '2', BEACH = '5', SEABED = '6';
    static final double[] GRASS_GREEN_INTERVAL = {2, 1000}, BEACH_INTERVAL = {-10, 2}, SEABED_INTERVAL = {-100, -10}; // 2 meters for beach high is too much but adjust with test in game

    static final String BOTTOM_WATER_FOR_AC_STR = "-100";
    static final double BOTTOM_WATER_FOR_AC = Double.parseDouble(BOTTOM_WATER_FOR_AC_STR);
    static final String HEIGHT_EXTENSION = ".height";
    
    public static void main(String[] args)
    {
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(HEIGHT_EXTENSION))
            {
                Disp.print("Working on: " + fName);
                ArrayList<String> lines = new ArrayList<String>();
                try
                {
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        lines.add(line);
                    }
                    scanner.close();
                    File biomeFile = new File(fName.replace(HEIGHT_EXTENSION, ".biomes"));
                    FileWriter fw = new FileWriter(biomeFile);
                    int linesSize = lines.size();
                    for(int linesIndex = 0; linesIndex < linesSize; linesIndex += 2)
                    {
                        String line = lines.get(linesIndex);
                        String[] parts = line.split(" ");
                        int partsLength = parts.length;
                        for(int partsIndex = 0; partsIndex < partsLength; partsIndex += 2)
                        {
                            String part = parts[partsIndex];
                            double altitude;
                            if(part.equals("N"))
                                altitude = BOTTOM_WATER_FOR_AC;
                            else
                                altitude = Double.parseDouble(part);
                            fw.write(getBiome(altitude));
                        }
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
    }
    
    static boolean isInInterval(double altitude, double[] interval)
    {
        return interval[0] <= altitude && altitude <= interval[1];
    }
    
    static char getBiome(double altitude)
    {
        if(isInInterval(altitude, GRASS_GREEN_INTERVAL))
            return GRASS_GREEN;
        else if(isInInterval(altitude, BEACH_INTERVAL))
            return BEACH;
        else // can return seabed for extrem values
            return SEABED;
    }
}