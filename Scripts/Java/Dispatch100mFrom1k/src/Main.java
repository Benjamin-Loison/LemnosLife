import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        int len = files.length;
        for(int i = 0; i < len; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".chunk"))
            {
                Disp.print("(" + i + "/" + len + ") Working on: " + fName);
                HashMap<String, ArrayList<String>> map = new HashMap<String, ArrayList<String>>();
                try
                {
                    Scanner scan = new Scanner(file);
                    while(scan.hasNextLine())
                    {
                        String line = scan.nextLine();
                        String[] parts = line.split(" ");
                        Double[] cooPur = {Double.parseDouble(parts[1]), Double.parseDouble(parts[2])};
                        Byte[] cooSbChk = new Byte[2];
                        for(byte j = 0; j <= 1; j++)
                        {
                            double tmp = cooPur[j] % 1000;
                            cooSbChk[j] = (byte)((tmp - (tmp % 100)) / 100);
                        }
                        ArrayList<String> lines;
                        String fnChk = cooSbChk[0] + " " + cooSbChk[1];
                        if(!map.containsKey(fnChk))
                        {
                            lines = new ArrayList<String>();
                        }
                        else
                        {
                            lines = map.get(fnChk);
                        }
                        lines.add(line);
                        map.put(fnChk, lines);
                    }
                    scan.close();
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                }
                if(!file.delete())
                {
                    Disp.print("FATAL ERROR: can't delete file: " + fName);
                }
                try
                {
                    FileWriter fw = new FileWriter(file);
                    Iterator<String> it = map.keySet().iterator();
                    while(it.hasNext())
                    {
                        String cooSbChk = it.next();
                        //Disp.print(cooSbChk);
                        Iterator<String> ite = map.get(cooSbChk).iterator();
                        fw.write(cooSbChk + '\n');
                        while(ite.hasNext())
                        {
                            String line = ite.next();
                            fw.write(line);
                            if(ite.hasNext() || it.hasNext())
                                fw.write('\n');
                        }
                    }
                    fw.close();
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                }
            }
            else
            {
                Disp.print("(" + i + "/" + len + ") Ignoring: " + fName);
            }
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }

}