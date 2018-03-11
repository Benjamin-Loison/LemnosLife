package fr.altiscraft.benjaminloison.common;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

import fr.altiscraft.benjaminloison.api.Disp;

public class FileConverter
{
    public static boolean force = false;
    public static final String PROGRAM_ID = "[CP-ALG] ";
    public static String mapName;
    public static File mapToConvertFile, mapConvertedFile;
    
    public static boolean initializeMapFile(String pathToToConvertFile)
    {
        mapToConvertFile = new File(pathToToConvertFile);
        if(!mapToConvertFile.exists())
            Disp.print("The file: " + pathToToConvertFile + " doesn't exist !", true);
        mapToConvertFile = writeTmpFile(pathToToConvertFile);
        if(mapToConvertFile == null)
            Disp.print("There was an unexpected error with the writing temporary file !");
        if(!initializeMapName())
            Disp.print("There was an unexpected error with the map name initialization !", true);
        String pathToConvertedFile = mapName + ".map";
        mapConvertedFile = new File(pathToConvertedFile);
        if(mapConvertedFile.exists())
            if(force)
                mapConvertedFile.delete();
            else
                Disp.print("The file: " + pathToConvertedFile + " already exists !", true);
        return true;
    }
    
    public static File writeTmpFile(String path)
    {
        Disp.print("Extracting algorithm part of the log file...");
        if(!path.endsWith(".rpt"))
            Disp.print("The file: " + path + " doesn't end with .rpt !", true);
        path = path.replace(".rpt", ".tmp");
        File tmpFile = new File(path);
        if(tmpFile.exists())
            if(force)
                tmpFile.delete();
            else
                Disp.print("The file: " + path + " already exists !", true);
        try
        {
            FileWriter fw = new FileWriter(tmpFile);
            Scanner scan = new Scanner(mapToConvertFile), scanBis = new Scanner(mapToConvertFile);
            while(scan.hasNextLine())
            {
                scanBis.nextLine();
                String line = scan.nextLine();
                if(line.contains(PROGRAM_ID))
                {
                    fw.write(line);
                    if(scanBis.hasNextLine())
                        fw.write("\n");
                }
            }
            scanBis.close();
            scan.close();
            fw.close();
        }
        catch(IOException e)
        {
            e.printStackTrace();
            return null;
        }
        return tmpFile;
    }
    
    public static boolean initializeMapName()
    {
        Scanner scannerFileToConvert = null;
        try
        {
            scannerFileToConvert = new Scanner(mapToConvertFile);
            String prefix = "Map: ";
            while(scannerFileToConvert.hasNextLine())
            {
                String line = realOutput(scannerFileToConvert.nextLine());
                if(line.startsWith(prefix))
                {
                    mapName = line.replace(prefix, "");
                    scannerFileToConvert.close();
                    return true;
                }
            }
            scannerFileToConvert.close();
        }
        catch(FileNotFoundException e)
        {
            e.printStackTrace();
            return false;
        }
        return false;
    }
    
    public static String getModelName(String model)
    {
        String[] parts = model.split("\\\\");
        return parts[parts.length - 1].replace(".p3d", "");
    }

    public static boolean convertFromA3ToAC()
    {
        Scanner scannerFileToConvert = null;
        try
        {
            scannerFileToConvert = new Scanner(mapToConvertFile);
        }
        catch(FileNotFoundException e)
        {
            e.printStackTrace();
            return false;
        }
        FileWriter fw = null;
        try
        {
            boolean first = true;
            fw = new FileWriter(mapConvertedFile);
            while(scannerFileToConvert.hasNextLine())
            {
                String lineWithDate = scannerFileToConvert.nextLine();
                String line = realOutput(lineWithDate);
                if(line.contains("Strange convex component"))
                {
                    Disp.print("There is an error in the map: " + line);
                    continue;
                }
                String prefix = "Model: \"\"";
                if(line.startsWith(prefix))
                {
                    if(first)
                        first = false;
                    else
                        fw.write("\n");
                    String model = getModelName(line.replace(prefix, "").replace("\"\"", ""));
                    String pos = realOutput(scannerFileToConvert.nextLine());
                    pos = pos.replace("Pos: ", "");
                    String dir = realOutput(scannerFileToConvert.nextLine());
                    dir = dir.replace("Dir: ", "");
                    fw.write(model + " " + pos + " " + dir);
                }
            }
            fw.close();
        }
        catch(IOException e)
        {
            e.printStackTrace();
            scannerFileToConvert.close();
            return false;
        }
        scannerFileToConvert.close();
        return true;
    }
    
    public static String realOutput(String line)
    {
        String output = line.substring(line.indexOf(" ") + 1);
        if(output.startsWith("\""))
            output = output.substring(1, output.length());
        if(output.endsWith("\""))
            output = output.substring(0, output.length() - 1);
        return output.replace(PROGRAM_ID, "");
    }
}
