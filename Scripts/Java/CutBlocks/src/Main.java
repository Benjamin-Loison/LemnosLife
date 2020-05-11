import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class Main
{
    private static String chkWorkPath = "-1 -1";
    private static String ext = ".block";
    private static File chkWorkFile = new File(chkWorkPath + ext);
    private static FileWriter fw = null;
    private static boolean firstWrite = true;

    public static void main(String[] args)
    {
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".log"))
            {
                Disp.print("Working on: " + fName);
                if(file.exists())
                {
                    try
                    {
                        Scanner scan = new Scanner(file);
                        while(scan.hasNextLine())
                        {
                            String line = scan.nextLine();
                            if(line.contains("[CPAGH] "))
                            {
                                String[] parts = line.split(" ");
                                String newLine = parts[parts.length - 1];
                                if(newLine.contains("*"))
                                {
                                    String[] starParts = newLine.split("\\*");
                                    chkWorkPath = starParts[0] + " " + starParts[1];
                                    Disp.print("Now working on chunk: " + chkWorkPath);
                                    chkWorkFile = new File(chkWorkPath + ext);
                                    if(fw != null)
                                        fw.close();
                                    fw = new FileWriter(chkWorkFile);
                                    firstWrite = true;
                                }
                                else
                                {
                                    if(firstWrite)
                                    {
                                        firstWrite = false;
                                        fw.write(newLine);
                                    }
                                    else
                                        fw.write("\n" + newLine);
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
            }
            else
                Disp.print("Do not work on: " + fName);
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}