import java.io.File;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Time.initializeTimer();
        String FOLDER = "height", EXTENSION = "height";
        File currentFolder = new File(FOLDER), files[] = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith("." + EXTENSION))
            {
                Disp.print("Working on: " + fName);
                file.renameTo(new File(FOLDER + File.separatorChar + fName + ".tmp"));
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
                String fNameWithoutExt = fName.replace("." + EXTENSION + ".tmp", "");
                Disp.print(fNameWithoutExt);
                String[] newNameParts = fNameWithoutExt.split(" ");
                file.renameTo(new File(FOLDER + File.separatorChar + newNameParts[0] + " " + (29 - Integer.parseInt(newNameParts[1])) + "." + EXTENSION));
            }
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}