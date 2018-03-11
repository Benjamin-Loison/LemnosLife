package fr.altiscraft.benjaminloison.api;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import fr.altiscraft.benjaminloison.common.FileConverter;

public class Partitioning
{
    public static int partitioningSize = 0;
    
    public static void initialize(String param)
    {
        try
        {
            partitioningSize = Integer.parseInt(param);
            if(partitioningSize < 0)
                Disp.print("Interger given is negative !", true);
        }
        catch(NumberFormatException nfe)
        {
            nfe.printStackTrace();
            Disp.print("Integer given for partitioning size is not correct formatted !", true);
        }
    }
    
    public static void write(String all)
    {
        String[] parts = all.split(" ");
        double x = Double.parseDouble(parts[1]);
        double y = Double.parseDouble(parts[2]);
        int xF = (int)((x - (x % partitioningSize)) / partitioningSize);
        int yF = (int)((y - (y % partitioningSize)) / partitioningSize);
        try
        {
            File chunk = new File("Maps" + File.separatorChar + FileConverter.mapName + File.separatorChar + xF + "_" + yF + ".map");
            if(!chunk.exists())
            {
                FileWriter fw = new FileWriter(chunk);
                fw.write(all);
                fw.close();
            }
            else
            {
                FileWriter fw = new FileWriter(chunk, true);
                fw.write("\n" + all);
                fw.close();
            }
        }
        catch(IOException e)
        {
            e.printStackTrace();
            Disp.print("Error while writing !", true);
        }
    }
}
