import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    private static final double BOTTOM_WATER_FOR_AC = -100;

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
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scan = new Scanner(file);
                    int x = -1, y = -1;
                    ArrayList<String> content = new ArrayList<String>();
                    while(scan.hasNextLine())
                    {
                        String line = scan.nextLine();
                        String[] parts = line.split(" ");
                        int partsLength = parts.length;
                        if(partsLength == 3) // meta data
                        {
                            String body = parts[2];
                            if(body.contains("B")) // begin
                            {
                                String[] metaPart = body.split("B");
                                x = Integer.parseInt(metaPart[0]);
                                y = Integer.parseInt(metaPart[1]);
                                content = new ArrayList<String>();
                                Disp.print("Working on chunk: " + x + " " + y);
                            }
                            else // end
                            {
                                if(isUsefull(content))
                                {
                                    File chk = new File(x + " " + y + ".height");
                                    FileWriter fw = new FileWriter(chk);
                                    int contentSize = content.size();
                                    for(int lineContent = 0; lineContent < contentSize; lineContent++)
                                    {
                                        fw.write(content.get(lineContent).replaceAll(".00 ", " ").replaceAll("-185.97", "N").replaceAll(BOTTOM_WATER_FOR_AC + "", "N"));
                                        if(lineContent != contentSize - 1)
                                        {
                                            fw.write("\n");
                                        }
                                    }
                                    fw.close();
                                }
                                else
                                {
                                    Disp.print("Chunk " + x + " " + y + " is useless, not writing !");
                                }
                                Disp.print("End work on chunk: " + x + " " + y);
                            }
                        }
                        else
                        {
                            String body = "";
                            for(int column = 2; column < partsLength; column++)
                            {
                                String height = parts[column];
                                if(!height.equals("F"))
                                {
                                    double heightDb = Double.parseDouble(height);
                                    if(heightDb >= BOTTOM_WATER_FOR_AC)
                                    {
                                        body += height;
                                    }
                                    else
                                    {
                                        body += BOTTOM_WATER_FOR_AC;
                                    }
                                }
                                else
                                {
                                    body += height;
                                }
                                if(column != partsLength - 1)
                                {
                                    body += " ";
                                }
                            }
                            if(body.charAt(0) == 'F') // add to previous line
                            {
                                int index = content.size() - 1;
                                String oldLine = content.get(index);
                                content.remove(index);
                                content.add(oldLine + body.replace("F", "")); // remain a space because not replace "F " by ""
                            }
                            else
                            {
                                content.add(body);
                            }
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
            String[] heights = lineContent.split(" ");
            for(int column = 0; column < heights.length; column++)
            {
                String height = heights[column];
                if(!height.equals("-185.97" + "") && !height.equals(BOTTOM_WATER_FOR_AC + ""))
                {
                    return true;
                }
            }
        }
        return false;
    }
}