import java.io.File;
import java.text.DecimalFormat;
import java.util.Scanner;

public class Main
{
    private static final short[] ROADS_SIZE = {14, 10, 10, 10, 7};
    
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("."), files[] = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".txt"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scanner = new Scanner(file);
                    double sum = 0, longest = 0, shortest = 10000;
                    int longestIndex = -1, lineIndex = 0, shortestIndex = 0;
                    DecimalFormat df = new DecimalFormat("####0.00");
                    while(scanner.hasNextLine())
                    {
                        double partialSum = 0; // max segment road 800 meters
                        String line = scanner.nextLine(),
                                 lineParts[] = line.split("@"),
                                 lineParts0Parts[] = lineParts[0].split(" ");
                        for(int lineParts0PartsIndex = 1; lineParts0PartsIndex < lineParts0Parts.length; lineParts0PartsIndex++)
                        {
                            String[] lineParts0PartsIndexParts = lineParts0Parts[lineParts0PartsIndex].split(","),
                                     lineParts0PartsIndexMinus1Parts = lineParts0Parts[lineParts0PartsIndex - 1].split(",");
                            double xA = Double.parseDouble(lineParts0PartsIndexMinus1Parts[0]), yA = Double.parseDouble(lineParts0PartsIndexMinus1Parts[1]),
                                   xB = Double.parseDouble(lineParts0PartsIndexParts[0]), yB = Double.parseDouble(lineParts0PartsIndexParts[1]),
                                   distance = Math.sqrt(Math.pow(xB - xA, 2) + Math.pow(yB - yA, 2));
                            sum += distance;
                            partialSum += distance;
                        }
                        if(partialSum > longest)
                        {
                            longest = partialSum;
                            longestIndex = lineIndex;
                        }
                        if(partialSum < shortest)
                        {
                            shortest = partialSum;
                            shortestIndex = lineIndex;
                        }
                        int roadType = Integer.parseInt(lineParts[1]);
                        if(partialSum <= 2 * ROADS_SIZE[roadType])
                        {
                            Disp.print("Short roads: " + lineIndex + " " + partialSum + " " + roadType + " " + lineParts0Parts.length + " points");
                        }
                        lineIndex++;
                        //Disp.print(lineIndex + ": " + df.format(partialSum));
                        /*
                            469 18.22022228184689 1 2 points
                            470 16.630586279503135 1 2 points
                            471 19.111295089553032 1 2 points
                            566 18.487901449326323 1 2 points
                            569 17.06999999999971 1 2 points
                            1400 19.145448736957164 1 3 points
                        */
                    }
                    Disp.print("Longest: " + longestIndex + ": " + df.format(longest));
                    Disp.print("Shortest: " + shortestIndex + ": " + df.format(shortest));
                    Disp.print("All roads: " + df.format(sum));
                    scanner.close();
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