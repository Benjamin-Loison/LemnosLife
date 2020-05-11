import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("."), files[] = currentFolder.listFiles();
        Map<Integer, ArrayList<Integer>> modelsDir = new HashMap<Integer, ArrayList<Integer>>();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".objects"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        String[] lineParts = line.split(" ");
                        if(lineParts.length != 2)
                        {
                            int id = Integer.parseInt(lineParts[0]), dir = Integer.parseInt(lineParts[4]);
                            if(modelsDir.containsKey(id))
                            {
                                ArrayList<Integer> dirs = modelsDir.get(id);
                                if(!dirs.contains(dir))
                                    dirs.add(dir);
                                modelsDir.put(id, dirs);
                            }
                            else
                            {
                                ArrayList<Integer> array = new ArrayList<Integer>();
                                array.add(dir);
                                modelsDir.put(id, array);
                            }
                        }
                    }
                    scanner.close();
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
        Iterator<Integer> keys = modelsDir.keySet().iterator();
        int total = 0;
        while(keys.hasNext())
        {
            int key = keys.next(), dirsNumber = modelsDir.get(key).size();
            Disp.print(key + " " + dirsNumber);
            total += dirsNumber;
        }
        Disp.print(total);
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}