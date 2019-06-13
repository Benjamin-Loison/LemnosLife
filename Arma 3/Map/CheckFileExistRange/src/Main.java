import java.io.File;
import java.util.ArrayList;

public class Main
{
    public static void main(String[] args)
    {
        Time.initializeTimer();
        
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        ArrayList<String> chk1kExist = new ArrayList<String>();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".height") || fName.endsWith(".biomes") || fName.endsWith(".objects"))
            {
                Disp.print("Working on: " + fName);
                chk1kExist.add(fName.split("\\.")[0]);
            }
            else
            {
                Disp.print("Do not work on: " + fName);
            }
        }
        
        if(args.length < 2)
        {
            Disp.print("Provide x y (chk 1k)");
        }
        else
        {
            int xAsked = Integer.parseInt(args[0]), yAsked = Integer.parseInt(args[1]);
            int range = 1;
            boolean goFurther = true;
            while(goFurther)
            {
                for(int x = xAsked - range; x < xAsked + range; x++)
                {
                    for(int y = yAsked - range; y < yAsked + range; y++)
                    {
                        if(!chk1kExist.contains(x + " " + y))
                        {
                            goFurther = false;
                            break;
                        }
                    }
                }
                Disp.print("Range: " + range);
                range++;
            }
            Disp.print("Last range before file doesn't exist: " + range);
        }
        
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}