import java.io.File;
import java.util.ArrayList;

public class Main
{
    public static void listf(String directoryName, ArrayList<File> files)
    {
        File directory = new File(directoryName);

        File[] fList = directory.listFiles();
        if(fList != null)
            for(File file : fList)
            {
                String fileName = file.getName();
                if(fileName.equals("UpdaterTool.jar") || fileName.equals("logs.txt")) continue;
                if(file.isFile())
                    files.add(file);
                else if(file.isDirectory())
                {
                    if(file.listFiles().length == 0)
                        files.add(file);
                    else
                        listf(file.getAbsolutePath(), files);
                }
            }
    }

    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        ArrayList<File> files = new ArrayList<File>();
        listf(".", files);
        String finalStr = "";
        int filesSizeMinus1 = files.size() - 1;
        for(int filesIndex = 0; filesIndex < filesSizeMinus1 + 1; filesIndex++)
        {
            File file = files.get(filesIndex);
            String filePath = file.getAbsolutePath().replace("C:\\Users\\Benjamin LOISON\\Desktop\\UpdaterTool\\.\\", "").replace("\\", "/");
            if(!file.isFile()) filePath += "/";
            Disp.print(filePath);
            finalStr += filePath;
            if(filesIndex != filesSizeMinus1)
                finalStr += "&";
        }
        Disp.print(finalStr);
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}