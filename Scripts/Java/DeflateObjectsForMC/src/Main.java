import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    private static final int CHUNK_SIZE = 1000, SUB_CHUNK_SIZE = 100;
    
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("."), files[] = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".objects"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    String[] fNameParts = fName.replace(".objects", "").split(" ");
                    int chunkX = CHUNK_SIZE * Integer.parseInt(fNameParts[0]), chunkY = CHUNK_SIZE * Integer.parseInt(fNameParts[1]), subChunkX = -1, subChunkY = -1;
                    ArrayList<String> lines = new ArrayList<String>();
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        String[] lineParts = line.split(" ");
                        if(lineParts.length != 2)
                        {
                            lines.add(lineParts[0] + " " + (Double.parseDouble(lineParts[1]) + subChunkX) + " " + (Double.parseDouble(lineParts[2]) + subChunkY) + " " + lineParts[3] + " " + lineParts[4]);
                        }
                        else
                        {
                            subChunkX = chunkX + SUB_CHUNK_SIZE * Integer.parseInt(lineParts[0]);
                            subChunkY = chunkY + SUB_CHUNK_SIZE * Integer.parseInt(lineParts[1]);
                        }
                    }
                    scanner.close();
                    file.delete();
                    FileAPI.writeFile(file, lines);
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