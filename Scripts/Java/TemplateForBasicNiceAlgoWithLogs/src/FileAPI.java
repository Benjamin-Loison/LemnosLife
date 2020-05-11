import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;

public class FileAPI
{
    public static void writeFile(File file, ArrayList<String> content)
    {
        try
        {
            FileWriter fw = new FileWriter(file);
            int contentSize = content.size(), contentSizeMinus1 = contentSize - 1;
            for(int contentIndex = 0; contentIndex < contentSize; contentIndex++)
            {
                fw.write(content.get(contentIndex));
                if(contentIndex < contentSizeMinus1)
                    fw.write("\n");
            }
            fw.close();

        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    public static void writeFile(String path, ArrayList<String> content)
    {
        writeFile(new File(path), content);
    }
}