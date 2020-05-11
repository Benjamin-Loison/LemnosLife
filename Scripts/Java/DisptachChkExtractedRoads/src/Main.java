import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    private static final float RANGE = 20, PRECISION = 0.1F;
    
    public static void main(String[] args)
    {
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        ArrayList<String> roadsData = new ArrayList<String>();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".extracted"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scan = new Scanner(file);
                    float roadSegmentX = -1, roadSegmentY = -2, x = -3, y = -4, lineNb = 0;
                    while(scan.hasNextLine())
                    {
                        String line = scan.nextLine();
                        if(line.contains(" [ER] "))
                        {
                            String[] parts = line.split(" ");
                            String body = "";
                            int partsLength = parts.length;
                            for(int part = 2; part < partsLength; part++)
                            {
                                body += parts[part];
                                if(part != partsLength - 1)
                                {
                                    body += " ";
                                }
                            }
                            body = body.replaceAll("  ", " ");
                            String[] bodyParts = body.split(" ");
                            int bodyPartsLength = bodyParts.length;
                            if(bodyPartsLength == 1) // data
                            {
                                for(int xRelative = 0; xRelative < body.length(); xRelative++)
                                {
                                    char info = body.charAt(xRelative);
                                    if(info == '@')
                                    {
                                        x = roadSegmentX - RANGE + xRelative * PRECISION;
                                        float y0 = roadSegmentY - RANGE, y1 = lineNb * PRECISION;
                                        y = y0 + y1; // PRECISION ?
                                        Disp.print(roadSegmentY + " " + RANGE + " " + lineNb + " " + PRECISION + " " + y + " " + y0 + " " + y1);
                                        String roadToAdd = x + " " + y;
                                        if(roadsData.contains(roadToAdd))
                                        {
                                            roadsData.add(roadToAdd); // not good coordinates
                                        }
                                        else
                                        {
                                            //Disp.print("Do not add duplicated: " + roadToAdd); // .9999 with double...
                                        }
                                    }
                                }
                            }
                            else // meta data
                            {
                                if(bodyPartsLength == 6)
                                {
                                    roadSegmentX = Float.parseFloat(bodyParts[4]);
                                    roadSegmentY = Float.parseFloat(bodyParts[5]);
                                    //Disp.print("Working on road segment: " + roadSegmentX + " " + roadSegmentY);
                                }
                            }
                        }
                        lineNb++;
                    }
                    scan.close();
                    print(roadsData);
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
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
    
    private static void print(ArrayList<String> roads)
    {
        int roadsSize = roads.size();
        for(int road = 0; road < roadsSize; road++)
        {
            Disp.print(road + " / " + roadsSize + " " + roads.get(road));
        }
    }
}