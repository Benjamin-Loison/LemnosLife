import java.io.File;
import java.io.FileWriter;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            final int CHK_SIZE = 100, LEVEL = -100;
            File mapFolder = new File(".");
            File[] chks = mapFolder.listFiles();
            ArrayList<String> strucIdDb = new ArrayList<String>();

            int len = chks.length;
            for(int i = 0; i < len; i++)
            {
                HashMap<String, ArrayList<String>> chksWithStruc = new HashMap<String, ArrayList<String>>();
                File chk = chks[i];
                System.out.println(i + " / " + len + " - " + chk.getName());
                if(chk.getName().endsWith(".jar") || chk.getName().endsWith(".txt"))
                    continue;
                Scanner scanner = new Scanner(chk);
                while(scanner.hasNextLine())
                {
                    String line = scanner.nextLine();
                    if(line.equals(""))
                    {
                        scanner.close();
                        chk.delete();
                        continue;
                    }
                    String[] parts = line.split(" ");

                    String struc = parts[0];
                    if(!strucIdDb.contains(struc))
                        strucIdDb.add(struc);
                    String newLine = strucIdDb.indexOf(struc) + " ";

                    double[] coo = new double[3];
                    for(int j = 0; j < 3; j++)
                        coo[j] = round(Double.parseDouble(parts[j + 1]), 2);
                    if(coo[2] < LEVEL)
                        continue;
                    int dir = ((int)(round(Double.parseDouble(parts[4]), 0)));
                    newLine += coo[0] + " " + coo[1] + " " + coo[2] + " " + dir;

                    int[] cooChk = new int[2];
                    for(int j = 0; j < 2; j++)
                    {
                        cooChk[j] = ((int)coo[j]) % 1000;
                        cooChk[j] = (cooChk[j] - (cooChk[j] % CHK_SIZE)) / CHK_SIZE;
                    }
                    String key = cooChk[0] + " " + cooChk[1];
                    if(chksWithStruc.containsKey(key))
                    {
                        ArrayList<String> lines = chksWithStruc.get(key);
                        lines.add(newLine);
                        chksWithStruc.put(key, lines);
                    }
                    else
                    {
                        ArrayList<String> lines = new ArrayList<String>();
                        lines.add(newLine);
                        chksWithStruc.put(key, lines);
                    }
                }
                scanner.close();
                chk.delete();
                FileWriter fw = new FileWriter(chk);
                Iterator<String> keys = chksWithStruc.keySet().iterator(), keysTmp = chksWithStruc.keySet().iterator();
                /*if(keysTmp.hasNext())
                    keysTmp.next();
                else
                    continue;*/
                while(keys.hasNext())
                {
                    if(keysTmp.hasNext())
                        keysTmp.next();
                    String key = keys.next();
                    ArrayList<String> lines = chksWithStruc.get(key);
                    fw.write(key + "\n"); // TEST OPTIMIZATION LOUIS
                    for(int j = 0; j < lines.size() - 1; j++)
                        fw.write(lines.get(j)/*.replaceAll("\\.0", "")*/ + "\n"); // replace already done in OptimizeChkObj ?!
                    fw.write(lines.get(lines.size() - 1)/*.replaceAll("\\.0", "")*/); // backslash n tmp
                    if(keysTmp.hasNext())
                        fw.write("\n"); // do without chunk info
                }
                fw.close();
                if(chk.length() == 0)
                    chk.delete();
            }

            File strucIdDbFile = new File("strucIdDb.txt");
            FileWriter fw = new FileWriter(strucIdDbFile);
            for(int i = 0; i < strucIdDb.size() - 1; i++)
                fw.write(i + " " + strucIdDb.get(i) + "\n");
            int nb = strucIdDb.size() - 1;
            fw.write(nb + " " + strucIdDb.get(nb));
            fw.close();

        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    public static double round(double value, int places)
    {
        if(places < 0)
            throw new IllegalArgumentException();
        BigDecimal bd = new BigDecimal(value);
        bd = bd.setScale(places, RoundingMode.HALF_UP);
        return bd.doubleValue();
    }
}