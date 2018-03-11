package fr.altiscraft.benjaminloison.common;

import fr.altiscraft.benjaminloison.api.Disp;
import fr.altiscraft.benjaminloison.api.Number;
import fr.altiscraft.benjaminloison.api.Statistics;
import fr.altiscraft.benjaminloison.api.Time;

public class Main
{
	public static void main(String[] args)
	{
	    Time.initializeTimer();
	    if(args.length == 0)
	        Disp.print("Please provide a path to the file of the map to convert ! /!\\ And add -f to force removing extisting files /!\\", true);
	    for(int i = 1; i < args.length; i++)
	        if(args[i].equals("-f"))
	            FileConverter.force = true;
	    if(!FileConverter.initializeMapFile(args[0]))
	        Disp.print("Please provide a path to a file which exists !", true);
	    Statistics.statisticsAbout(FileConverter.mapToConvertFile, true);
	    if(!FileConverter.convertFromA3ToAC())
	        Disp.print("An unexpected error occured during the conversion, please look at the message above this one !", true);
	    Statistics.statisticsAbout(FileConverter.mapConvertedFile, false);
	    Disp.print("Conversion successfully done in " + Number.numberWithSpaces(Time.getExecuteTimeInMs()) + " milliseconds !");
	}
}