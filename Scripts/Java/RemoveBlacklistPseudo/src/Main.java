import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Time.initializeTimer();

            // load blacklist.txt (potential: depends on pseudo)
            File blacklistFile = new File("blacklist.txt");
            ArrayList<String> pseudoList = new ArrayList<String>();
            Scanner scan = new Scanner(blacklistFile);
            while(scan.hasNextLine())
            {
                String pseudo = scan.nextLine();
                
                /*firstName = name(firstName);
                lastName = name(lastName);
                pseudo = firstName + "_" + lastName;*/ // TODO: use in the other algorithm to restore names
                //if(!isFirstUpperCase(firstName) || !isFirstUpperCase(lastName)) continue;
                if(!isPseudoCorrect(pseudo)) continue;
                if(!pseudoList.contains(pseudo))
                    pseudoList.add(pseudo);
            }
            scan.close();

            // load treat.csv
            File treatFile = new File("treat.csv");
            ArrayList<String> lines = new ArrayList<String>();
            scan = new Scanner(treatFile);
            while(scan.hasNextLine())
            {
                String line = scan.nextLine();
                lines.add(line);
            }
            scan.close();
            
            treatFile.delete();
            
            // treat treat.csv
            int linesSize = lines.size(), pseudoSize = pseudoList.size();
            ArrayList<String> newLines = new ArrayList<String>();
            for(int lineIndex = 0; lineIndex < linesSize; lineIndex++)
            {
                String line = lines.get(lineIndex);
                boolean isBlacklisted = false;
                for(int pseudoIndex = 0; pseudoIndex < pseudoSize; pseudoIndex++)
                {
                    if(line.contains(pseudoList.get(pseudoIndex)))
                    {
                        isBlacklisted = true;
                        break;
                    }
                }
                if(!isBlacklisted)
                    newLines.add(line);
            }
            
            // write treat.csv
            FileWriter fw = new FileWriter(treatFile);
            int newLinesSize = newLines.size();
            for(int newLinesIndex = 0; newLinesIndex < newLinesSize; newLinesIndex++)
            {
                fw.write(newLines.get(newLinesIndex));
                if(newLinesIndex != newLinesSize - 1)
                    fw.write("\n");
            }
            fw.close();
            
            Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    
    private static boolean isPseudoCorrect(String pseudo)
    {
        if(!pseudo.contains("_")) return false;
        String[] parts = pseudo.split("_");
        if(parts.length != 2) return false;
        String firstName = parts[0], lastName = parts[1];
        if(firstName.length() < 3 || lastName.length() < 3) return false;
        if(!isAlphabetic(firstName) || !isAlphabetic(lastName)) return false;
        return true;
    }
    
    private static boolean isAlphabetic(String string)
    {
        for(int stringIndex = 0; stringIndex < string.length(); stringIndex++)
        {
            char chr = string.charAt(stringIndex);
            int charInt = (int)chr; 
            if((charInt < 97 || charInt > 122) && (charInt < 65 || charInt > 90)) return false;
        }
        return true;
    }
    
    private static boolean isFirstUpperCase(String string)
    {
        String firstChar = string.charAt(0) + "";
        return firstChar.equals(firstChar.toUpperCase());
    }
    
    private static String name(String string)
    {
        return (string.charAt(0) + "").toUpperCase() + string.toLowerCase().substring(1);
    }
}