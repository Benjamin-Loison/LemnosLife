import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    private static final int CHK_SIZE = 1000;
    
    public static void main(String[] args)
    {
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".objects")) // endsWith
            {
                Disp.print("Working on: " + fName);
                String[] indexFile = fName.replace(".objects", "").split(" ");
                int x = Integer.parseInt(indexFile[0]), y = Integer.parseInt(indexFile[1]);
                int xRemove = x * CHK_SIZE, yRemove = y * CHK_SIZE;
                //System.out.println(y + " " + CHK_SIZE + " " + yRemove);
                ArrayList<String> lines = new ArrayList<String>();
                try
                {
                    Scanner scan = new Scanner(file);
                    while(scan.hasNextLine())
                    {
                        String line = scan.nextLine();
                        lines.add(line);
                    }
                    scan.close();
                    file.delete();
                    FileWriter fw = new FileWriter(file);
                    int linesSize = lines.size();
                    for(int line = 0; line < linesSize; line++)
                    {
                        String currentLine = lines.get(line);
                        String[] parts = currentLine.split(" ");
                        if(parts.length == 5)
                        {
                            // X
                            double cX = Double.parseDouble(parts[1]);
                            String[] xParts = parts[1].split("\\.");
                            String decimalX = xParts[1];
                            String integerX = xParts[0];
                            int intX = Integer.parseInt(integerX) - xRemove;
                            double newX = Double.parseDouble((intX % 100) + "." + decimalX);
                            
                            // Y
                            double cY = Double.parseDouble(parts[2]);
                            String[] yParts = parts[2].split("\\.");
                            String decimalY = yParts[1];
                            String integerY = yParts[0];
                            int intY = Integer.parseInt(integerY) - yRemove;
                            double newY = Double.parseDouble((intY % 100) + "." + decimalY);
                            
                            //double newX = cX - xRemove;
                            //double newY = cY - yRemove;
                            
                            //System.out.println(cX + " " + xRemove + " " + newX + "@" + cY + " " + yRemove + " " + newY);
                            fw.write((parts[0] + " " + newX + " " + newY + " " + parts[3] + " " + parts[4]).replaceAll("\\.0 ", " "));
                        }
                        else
                        {
                            fw.write(currentLine);
                        }
                        if(line != linesSize - 1)
                            fw.write("\n");
                    }
                    fw.close();
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                }
            }
            else
            {
                //Disp.print("Do not work on: " + fName);
            }
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}