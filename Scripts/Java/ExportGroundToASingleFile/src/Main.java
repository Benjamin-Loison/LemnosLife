import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();
        File currentFolder = new File("ground");
        File[] files = currentFolder.listFiles();
        Map<String, ArrayList<String>> map = new HashMap<String, ArrayList<String>>();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".height"))
            {
                Disp.print("Working on: " + fName);
                ArrayList<String> lines = new ArrayList<String>();
                try
                {
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine(), newLine = "";
                        String[] lineParts = line.split(" ");
                        int linePartsLength = lineParts.length;
                        for(int j = 0; j < linePartsLength; j++)
                        {
                            String value = lineParts[j];
                            if(value.equals("N")) value = "-100.00";
                            boolean positive = value.charAt(0) != '-';
                            value = value.replace("-", "");
                            if(value.contains(".")) // warning no regex !
                            {
                                String[] valueParts = value.split("\\."); // warning regex !
                                if(valueParts[1].length() == 1)
                                    valueParts[1] += '0';
                                for(int k = valueParts[0].length(); k < 3; k++)
                                    valueParts[0] = '0' + valueParts[0];
                                value = valueParts[0] + '.' + valueParts[1];
                            }
                            else
                            {
                                for(int k = value.length(); k < 3; k++)
                                    value = '0' + value;
                                value += ".00";
                            }
                            if(positive)
                                value = '+' + value;
                            else
                                value = '-' + value;
                            newLine += value;
                            if(j < linePartsLength - 1)
                                newLine += " ";
                        }
                        lines.add(newLine);
                    }
                    scanner.close();
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                }
                map.put(fName.replace(".height", ""), lines);
            }
            else
            {
                Disp.print("Do not work on: " + fName);
            }
        }
        ArrayList<String> empty = new ArrayList<String>();
        String emptyLine = "";
        for(int column = 0; column < 251; column++)
        {
            if(column < 250)
                emptyLine += "-100.00 ";
            else
                emptyLine += "-100.00";
        }
        for(int line = 0; line < 251; line++)
            empty.add(emptyLine);
        for(int x = 0; x < 30; x++)
            for(int y = 0; y < 30; y++)
            {
                String key = x + " " + y;
                if(!map.containsKey(key))
                    map.put(key, empty);
            }
        try
        {
            FileWriter fw = new FileWriter(new File("ground.txt"));
            for(int chkHeight = 0; chkHeight < 30; chkHeight++)
            {
                for(int lineIndex = 0; lineIndex < 251; lineIndex++)
                {
                    String line = "";
                    for(int chkColumn = 0; chkColumn < 30; chkColumn++)
                    {
                        String fileLine = map.get(chkHeight + " " + chkColumn).get(lineIndex);
                        //Disp.print(fileLine);
                        line += fileLine;
                        if(chkColumn < 29)
                            line += " ";
                    }
                    fw.write(line + "\n");
                }
            }
            fw.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}