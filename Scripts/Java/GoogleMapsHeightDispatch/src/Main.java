import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class Main
{
    static final int LINE_NUMBER = 3558, COLUMN_NUMBER = 4274, SUB_CHK_NB = 101;
    static double[][] test = new double[LINE_NUMBER][COLUMN_NUMBER]; // 3 510 * 3 983 = 13 980 330

    public static void main(String[] args)
    {
        Time.initializeTimer();
        File currentFolder = new File(".");
        File[] files = currentFolder.listFiles();
        for(int i = 0; i < files.length; i++)
        {
            File file = files[i];
            String fName = file.getName();
            if(fName.endsWith(".gmap"))
            {
                Disp.print("Working on: " + fName);
                try
                {
                    //int lineIndex = 0, columnIndex = 0;
                    Scanner scanner = new Scanner(file);
                    while(scanner.hasNextLine())
                    {
                        String line = scanner.nextLine();
                        String[] parts = line.split(" ");
                        int lineIndex = Integer.parseInt(parts[0]), columnIndex = Integer.parseInt(parts[1]);
                        double height = Double.parseDouble(parts[2]);
                        test[lineIndex][columnIndex] = height;
                        //columnIndex++;
                        /*if(columnIndex == COLUMN_NUMBER)
                        {
                            lineIndex++;
                            columnIndex = 0;
                        }*/
                    }
                    scanner.close();
                    Disp.print("Reading finished");
                    // displayArray();
                    int chunkLine = (LINE_NUMBER - (LINE_NUMBER % SUB_CHK_NB)) / SUB_CHK_NB, chunkColumn = (COLUMN_NUMBER - (COLUMN_NUMBER % SUB_CHK_NB)) / SUB_CHK_NB;
                    for(int chunkLineIndex = 0; chunkLineIndex < chunkLine; chunkLineIndex++)
                    {
                        int chunkLineIndexHundred = chunkLineIndex * 100;
                        for(int chunkColumnIndex = 0; chunkColumnIndex < chunkColumn; chunkColumnIndex++)
                        {
                            int chunkColumnIndexHundred = chunkColumnIndex * 100;
                            File chkFile = new File(chunkLineIndex + " " + chunkColumnIndex + ".height");
                            FileWriter fw = new FileWriter(chkFile);
                            for(int chkFileLineIndex = 0; chkFileLineIndex < SUB_CHK_NB; chkFileLineIndex++)
                            {
                                for(int chkFileColumnIndex = 0; chkFileColumnIndex < SUB_CHK_NB; chkFileColumnIndex++)
                                {
                                    String height = test[chunkLineIndexHundred + chkFileLineIndex][chunkColumnIndexHundred + chkFileColumnIndex] + "", newHeight = height;
                                    String[] parts = height.split("\\.");
                                    if(parts.length == 2)
                                    {
                                        String part0 = parts[0], part1 = parts[1];
                                        int parts1Len = part1.length();
                                        if(parts1Len > 2)
                                            parts1Len = 2;
                                        newHeight = part0 + "." + part1.substring(0, parts1Len);
                                    }
                                    if(newHeight == "-11")
                                        Disp.print(chkFile.getName() + " " + height);
                                    fw.write(newHeight);
                                    if(chkFileColumnIndex != SUB_CHK_NB - 1)
                                    {
                                        fw.write(" ");
                                    }
                                }
                                if(chkFileLineIndex != SUB_CHK_NB - 1)
                                {
                                    fw.write("\n");
                                }
                            }
                            fw.close();
                        }
                    }
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                }

            }
            else
            {
                Disp.print("Do not work on: " + fName);
            }
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }

    private static void displayArray()
    {
        for(int lineIndex = 0; lineIndex < LINE_NUMBER; lineIndex++)
        {
            for(int columnIndex = 0; columnIndex < COLUMN_NUMBER; columnIndex++)
            {
                Disp.print(test[lineIndex][columnIndex]);
            }
        }
    }

    private static String replaceLastZeros(String str)
    {
        while((str.charAt(str.length() - 1) == '0' || str.charAt(str.length() - 1) == '.') && str.length() >= 2)
            str = str.substring(0, str.length() - 1);
        return str;
    }
}