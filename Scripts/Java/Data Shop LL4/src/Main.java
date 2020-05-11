import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    static ArrayList<String> arrayList = new ArrayList<String>();
    static ArrayList<String> lines = new ArrayList<String>();

    private static String addZeros(String input)
    {
        //Disp.print(input);
        String parts[] = input.split("\\."), out = "";
        for(int j = 0; j < 4; j++)
        {
            String part = parts[j];
            int max = 3 - part.length();
            //Disp.print(max);
            for(int i = 0; i < max; i++)
                part = "0" + part;
            out += part;
        }
        //Disp.print(out);
        return out;
    }

    public static void main(String[] args)
    {
        Time.initializeTimer();
        try
        {
            Scanner scanner = new Scanner(new File("ip.txt"));
            FileWriter fw = new FileWriter(new File("range.txt"));
            int threads = 0;
            while(scanner.hasNextLine())
            {
                String line = scanner.nextLine(), lineParts[] = line.split(" ");
                if(lineParts.length == 2)
                {
                    //if(arrayList.contains(lineParts[0]))
                      //  continue;
                    arrayList.add(lineParts[0]);
                    Thread th = new Thread()
                    {
                        public void run()
                        {
                            test(lineParts);
                        }
                    };
                    threads++;
                    th.start();
                    Thread.sleep(250);
                }
            }
            while(lines.size() == threads)
            {
                Disp.print("Waiting: " + threads + " " + lines.size());
                Thread.sleep(50);
            }
            for(int i = 0; i < lines.size(); i++)
            {
                fw.write(lines.get(i));
            }
            fw.close();
            scanner.close();
        }
        catch(Exception exception)
        {
            exception.printStackTrace();
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}