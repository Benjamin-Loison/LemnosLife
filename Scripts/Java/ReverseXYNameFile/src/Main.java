import java.io.File;
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
            if(fName.endsWith(".height"))
            {
                Disp.print("Working on: " + fName);
                file.renameTo(new File(fName + ".tmp"));
            }
            else
            {
                Disp.print("Do not work on: " + fName);
            }
        }
        files = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".tmp"))
            {
                String fNameWithoutExt = fName.replace(".height.tmp", "");
                Disp.print(fNameWithoutExt);
                String[] newNameParts = fNameWithoutExt.split(" ");
                file.renameTo(new File(newNameParts[1] + " " + newNameParts[0] + ".height"));
            }
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}