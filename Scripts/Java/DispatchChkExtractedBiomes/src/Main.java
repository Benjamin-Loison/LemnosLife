import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".extracted"))
            {
                try
                {
                    Disp.print("Working on: " + fName);
                    Scanner scan = new Scanner(file);
                    int x = -1, y = -1;
                    ArrayList<String> content = new ArrayList<String>();
                    while(scan.hasNextLine())
                    {
                        String line = scan.nextLine();
                        String[] parts = line.split(" ");
                        String body = parts[2];
                        if(body.length() < 10) // meta data
                        {
                            if(body.contains("B")) // begin
                            {
                                String bodyParts[] = body.split("B");
                                x = Integer.parseInt(bodyParts[0]);
                                y = Integer.parseInt(bodyParts[1]);
                                content = new ArrayList<String>();
                            }
                            else // E - END
                            {
                                if(isUsefull(content))
                                {
                                    File chk = new File(x + " " + y + ".biomes");
                                    FileWriter fw = new FileWriter(chk);
                                    int contentSize = content.size();
                                    for(int contentLine = 0; contentLine < contentSize; contentLine++)
                                    {
                                        fw.write(content.get(contentLine));
                                        if(contentLine != contentSize - 1)
                                        {
                                            fw.write("\n");
                                        }
                                    }
                                    fw.close();
                                }
                            }
                        }
                        else // data
                        {
                            content.add(body);
                        }
                    }
                    scan.close();
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
    
    private static boolean isUsefull(ArrayList<String> content)
    {
        for(int line = 0; line < content.size(); line++)
        {
            String lineContent = content.get(line);
            for(int biom = 0; biom < lineContent.length(); biom++)
            {
                if(lineContent.charAt(biom) != '6')
                {
                    return true;
                }
            }
        }
        return false;
    }
}