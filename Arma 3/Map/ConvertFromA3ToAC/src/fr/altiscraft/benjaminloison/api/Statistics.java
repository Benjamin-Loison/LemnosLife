package fr.altiscraft.benjaminloison.api;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;

import fr.altiscraft.benjaminloison.common.FileConverter;

public class Statistics
{
    public static void statisticsAbout(File file, boolean isFileToConvert)
    {
        Disp.print("Statistics about the file: " + file.getName());
        commonStatistics(file);
        if(isFileToConvert)
        {
            statsGen(file);
            statsObjects(file);
        }
    }

    private static void commonStatistics(File file)
    {
        statsLigns(file);
        statsSize(file);
    }

    private static void statsObjects(File file)
    {
        Scanner scanner = null;
        try
        {
            int modelsNumber = 0;
            Map<String, Integer> models = new HashMap<String, Integer>();
            scanner = new Scanner(file);
            while(scanner.hasNextLine())
            {
                String line = scanner.nextLine();
                String output = FileConverter.realOutput(line);
                if(output.contains("Model"))
                {
                    modelsNumber++;
                    String model = output.replace("Model: \"\"", "").replaceAll("\"", "");
                    if(models.containsKey(model))
                        models.put(model, models.get(model) + 1);
                    else
                        models.put(model, 1);
                }
            }
            scanner.close();
            Disp.print("The file has " + Number.numberWithSpaces(modelsNumber) + " objects.");
            File modelsFile = new File("modelsInfo.txt");
            if(modelsFile.exists())
                if(FileConverter.force)
                    modelsFile.delete();
                else
                    Disp.print("The file: " + modelsFile.getAbsolutePath() + " already exists !", true);
            try
            {
                FileWriter fw = new FileWriter(modelsFile);
                fw.write("There are " + Number.numberWithSpaces(models.keySet().size() / 2) + " different models:\n");
                models = MapUtil.sortByValue(models);
                Iterator<String> it = models.keySet().iterator(), itTmp = it;
                while(it.hasNext())
                {
                    itTmp.next();
                    String key = it.next();
                    int value = models.get(key);
                    fw.write(Number.numberWithSpaces(value) + " " + key + " " + FileConverter.getModelName(key));
                    if(itTmp.hasNext())
                        fw.write("\n");
                }
                fw.close();
                Disp.print("More informations about the models in the file: " + modelsFile.getAbsolutePath());
            }
            catch(IOException e)
            {
                e.printStackTrace();
            }
        }
        catch(FileNotFoundException e)
        {
            e.printStackTrace();
        }
    }

    private static void statsSize(File file)
    {
        Disp.print("The file size is about " + Number.numberWithSpaces(file.length()) + " bytes.");
    }

    private static void statsLigns(File file)
    {
        Scanner scanner = null;
        try
        {
            int lignsNumber = 0;
            scanner = new Scanner(file);
            while(scanner.hasNextLine())
            {
                lignsNumber++;
                scanner.nextLine();
            }
            scanner.close();
            Disp.print("The file has " + Number.numberWithSpaces(lignsNumber) + " ligns.");
        }
        catch(FileNotFoundException e)
        {
            e.printStackTrace();
        }
    }

    private static void statsGen(File file)
    {
        int generationTime = getGenerationTimeInSeconds(file);
        if(generationTime > 0)
            Disp.print("The file was generated in " + Number.numberWithSpaces(generationTime) + " seconds.");
        else
            Disp.print("The generation time isn't available.");
    }

    private static int getGenerationTimeInSeconds(File file)
    {
        Scanner scanner = null;
        try
        {
            scanner = new Scanner(file);
        }
        catch(FileNotFoundException e)
        {
            e.printStackTrace();
            return -1;
        }
        int beginTime = -1, lastTime = -1;
        while(scanner.hasNextLine())
        {
            String lign = scanner.nextLine().replaceAll("ï»¿", ""); // PATCH: UTF-8 without BOM
            String[] parts = lign.split(" ");
            if(parts.length >= 2)
            {
                String timePart = parts[0];
                String[] timeParts = timePart.split(":");
                if(timeParts.length == 3)
                {
                    if(beginTime == -1)
                        beginTime = getTime(timePart);
                    else
                        lastTime = getTime(timePart);
                }
            }
        }
        scanner.close();
        return lastTime - beginTime;
    }

    private static int getTime(String timePart)
    {
        String[] timeParts = timePart.split(":");
        int hours = Integer.parseInt(timeParts[0]);
        int minutes = Integer.parseInt(timeParts[1]);
        int seconds = Integer.parseInt(timeParts[2]);
        return hours * 3600 + minutes * 60 + seconds;
    }
}
