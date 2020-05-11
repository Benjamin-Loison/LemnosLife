import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("."), files[] = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".height"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scanner = new Scanner(file);
                    double[][] heights = new double[251][];
                    int[][] newHeights = new int[1000][];
                    int heightsIndex = 0;
                    while(scanner.hasNextLine())
                    {
                        double[] lineHeights = new double[251];
                        String line = scanner.nextLine();
                        String[] lineParts = line.split(" ");
                        for(int linePartsIndex = 0; linePartsIndex < 251; linePartsIndex++)
                        {
                            String element = lineParts[linePartsIndex];
                            if(element.equals("N"))
                                lineHeights[linePartsIndex] = 0;
                            else
                                lineHeights[linePartsIndex] = (Double.parseDouble(element) + 100) * (255.0 / 449.13);
                        }
                        heights[heightsIndex] = lineHeights;
                        heightsIndex++;
                    }
                    for(int y = 0; y < 1000; y++)
                    {
                        int[] newHeightsLine = new int[1000];
                        for(int x = 0; x < 1000; x++)
                        {
                            newHeightsLine[x] = -999;
                        }
                        newHeights[y] = newHeightsLine;
                    }
                    scanner.close();
                    for(int y = 0; y < 250; y++)
                        for(int x = 0; x < 250; x++)
                        {
                            double topLeft = heights[y][x], topRight = heights[y][x + 1], bottomLeft = heights[y + 1][x], bottomRight = heights[y + 1][x + 1],
                                   vecTopLeftTopRight = topRight - topLeft, vecTopLeftBottomLeft = bottomLeft - topLeft, vecBottomLeftBottomRight = bottomRight - bottomLeft, vecTopRightBottomRight = bottomRight - topRight,
                                   h01 = topLeft + vecTopLeftTopRight / 3, h02 = topLeft + 2 * vecTopLeftTopRight / 3, h10 = topLeft + vecTopLeftBottomLeft / 3, h20 = topLeft + 2 * vecTopLeftBottomLeft / 3,
                                   h31 = bottomLeft + vecBottomLeftBottomRight / 3, h32 = bottomLeft + 2 * vecBottomLeftBottomRight / 3, h13 = topRight + vecTopRightBottomRight / 3, h23 = topRight + 2 * vecTopRightBottomRight / 3,
                                   vecH10H13 = h13 - h10, vecH20H23 = h23 - h20, // or moyenne avec les deux verticales ?
                                   h11 = h10 + vecH10H13 / 3, h12 = h10 + 2 * vecH10H13 / 3,
                                   h21 = h20 + vecH20H23 / 3, h22 = h20 + 2 * vecH20H23 / 3;

                            int nY = y * 4, nX = x * 4;
                            newHeights[nY][nX] = r(topLeft);
                            newHeights[nY][nX + 1] = r(h01);
                            newHeights[nY][nX + 2] = r(h02);
                            newHeights[nY][nX + 3] = r(topRight);
                            
                            newHeights[nY + 1][nX] = r(h10);
                            newHeights[nY + 1][nX + 1] = r(h11);
                            newHeights[nY + 1][nX + 2] = r(h12);
                            newHeights[nY + 1][nX + 3] = r(h13);
                            
                            newHeights[nY + 2][nX] = r(h20);
                            newHeights[nY + 2][nX + 1] = r(h21);
                            newHeights[nY + 2][nX + 2] = r(h22);
                            newHeights[nY + 2][nX + 3] = r(h23);
                            
                            newHeights[nY + 3][nX] = r(bottomLeft);
                            newHeights[nY + 3][nX + 1] = r(h31);
                            newHeights[nY + 3][nX + 2] = r(h32);
                            newHeights[nY + 3][nX + 3] = r(bottomRight);
                        }
                    file.delete();
                    FileWriter fw = new FileWriter(file);
                    for(int y = 0; y < 1000; y++)
                    {
                        for(int x = 0; x < 1000; x++)
                        {
                            fw.write(newHeights[y][x] + "");
                            if(x < 1000 - 1)
                                fw.write(" ");
                        }
                        if(y < 1000 - 1)
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
        Disp.closeLogger();
    }
    
    public static int r(double nb)
    {
        return (int)Math.round(nb);
    }
    
    
}