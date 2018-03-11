package fr.altiscraft.benjaminloison.common;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

import fr.altiscraft.benjaminloison.api.Disp;
import fr.altiscraft.benjaminloison.api.Partitioning;

public class FileConverter
{
    public static boolean force = false;
    public static final String PROGRAM_ID = "[CP-ALG] ";
    public static String mapName;
    public static File mapToConvertFile;

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

    public static void delete(File f)
    {
        if(f.isDirectory())
            for(File c : f.listFiles())
                delete(c);
        f.delete();
    }

    public static boolean convertFromA3ToAC()
    {
        Disp.print("Begin convertion...");
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
        File mapsFolder = new File("Maps");
        if(mapsFolder.exists())
            if(force)
                delete(mapsFolder);
            else
                Disp.print("The folder: " + mapsFolder.getAbsolutePath() + " already exists !", true);
        mapsFolder.mkdirs();
        File mapFolder = new File("Maps" + File.separatorChar + mapName);
        mapFolder.mkdirs();
        int modelNb = 0;
        while(scannerFileToConvert.hasNextLine())
        {
            String lineWithDate = scannerFileToConvert.nextLine();
            String line = realOutput(lineWithDate);
            String prefix = "Model: \"\"";
            if(line.startsWith(prefix))
            {
                String model = getModelName(line.replace(prefix, "").replace("\"\"", ""));
                String pos = realOutput(scannerFileToConvert.nextLine());
                pos = pos.replace("Pos: ", "");
                String dir = realOutput(scannerFileToConvert.nextLine());
                dir = dir.replace("Dir: ", "");
                String all = model + " " + pos + " " + dir;
                Partitioning.write(all);
                modelNb++;
                // Disp.print(Number.numberWithSpaces(modelNb) + " / " + Number.numberWithSpaces(Statistics.modelsNumber));
            }
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
