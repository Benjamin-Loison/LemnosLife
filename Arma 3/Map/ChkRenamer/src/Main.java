import java.io.File;

public class Main
{
    public static void main(String[] args) // useless with ConvertFromA3ToACPart on this eclipse folder
    {
        File[] chks = new File(".").listFiles();
        int len = chks.length;
        for(int i = 0; i < len; i++)
        {
            File chk = chks[i];
            String path = chk.getAbsolutePath();
            if(!path.endsWith(".map"))
                continue;
            chk.renameTo(new File(path.replace("_", " ").replace(".map", ".chunk")));
            System.out.println(i + " / " + len);
        }
    }
}