import java.io.File;
import java.util.Scanner;

public class Main
{
    /* Altis
        angleBiggest: 1.366785440467138
        roadId: 3
        segmentId: 8
     */
    
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("."), files[] = currentFolder.listFiles();
        double angleBiggest = -1;
        int roadId = -1, segmentId = -1, lineIndex = 0;
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
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        line = line.split("@")[0];
                        String[] lineParts = line.split(" ");
                        
                        for(int linePartsIndex = 0; linePartsIndex < lineParts.length - 2; linePartsIndex++)
                        {
                            String[] linePartParts = lineParts[linePartsIndex].split(","), linePartNextParts = lineParts[linePartsIndex + 1].split(","), linePartNextNextParts = lineParts[linePartsIndex + 2].split(",");
                            double x = Double.parseDouble(linePartParts[0]), y = Double.parseDouble(linePartParts[1]), xNext = Double.parseDouble(linePartNextParts[0]), yNext = Double.parseDouble(linePartNextParts[1]), xNextNext = Double.parseDouble(linePartNextNextParts[0]), yNextNext = Double.parseDouble(linePartNextNextParts[1]);
                            x -= xNext; x *= -1;
                            xNextNext -= xNext;
                            y -= yNext; y *= -1;
                            yNextNext -= yNext;
                            double angle = Math.abs(Math.acos((x * xNextNext + y * yNextNext) / (distance(x, y) * distance(xNextNext, yNextNext))));
                            if(angle > angleBiggest)
                            {
                                angleBiggest = angle;
                                roadId = lineIndex;
                                segmentId = linePartsIndex;
                                Disp.print(angle + " " + lineIndex + " " + linePartsIndex + " | " + x + " " + y + " " + xNextNext + " " + yNextNext);
                            }
                        }
                        lineIndex++;
                    }
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
        Disp.print("angleBiggest: " + angleBiggest);
        Disp.print("roadId: " + roadId);
        Disp.print("segmentId: " + segmentId);
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
    
    /*private static double distance(double x0, double y0, double x1, double y1)
    {
        return Math.sqrt(Math.pow(x0 - x1, 2) + Math.pow(y0 - y1, 2));
    }*/
    
    private static double distance(double x, double y)
    {
        return Math.sqrt(x * x + y * y);
    }
}