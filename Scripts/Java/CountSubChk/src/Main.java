import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            final int CHK_SIZE = 10;
            ArrayList<String> chks = new ArrayList<String>();
            File chk = new File("8_15.map");
            Scanner scanner = new Scanner(chk);
            while(scanner.hasNextLine())
            {
                String[] parts = scanner.nextLine().split(" ");
                int[] coo = new int[2];
                for(int i = 1; i < 3; i++)
                {
                    coo[i - 1] = (int)Double.parseDouble(parts[i]);
                    coo[i - 1] = (coo[i - 1] - (coo[i - 1] % CHK_SIZE)) / CHK_SIZE;
                }
                String chk_coo = coo[0] + "_" + coo[1];
                if(!chks.contains(chk_coo))
                    chks.add(chk_coo);
            }
            System.out.println(chks.size());
            scanner.close();
        }
        catch(FileNotFoundException e)
        {
            e.printStackTrace();
        }
    }
}