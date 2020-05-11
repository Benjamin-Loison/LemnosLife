import java.io.File;
import java.io.FileWriter;

public class Main
{
    static final int CHUNK_SIZE = 250;
    static final boolean WRITE = true, DISPLAY = true; // display can fuck upper a specific value

    public static void main(String[] args)
    {
        //Time.initializeTimer();

        String output = "";
        for(int lineIndex = 0; lineIndex <= CHUNK_SIZE; lineIndex++)
        {
            for(int columnIndex = 0; columnIndex <= CHUNK_SIZE; columnIndex++)
            {
                output += "N";
                if(columnIndex != CHUNK_SIZE)
                    output += " ";
            }
            if(lineIndex != CHUNK_SIZE)
                output += "\n";
        }

        if(WRITE)
        {
            File chkFile = new File("generated.height");
            try
            {
                FileWriter fw = new FileWriter(chkFile);
                fw.write(output);
                fw.close();
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
        }
        
        if(DISPLAY)
        {
            System.out.println(output);
            //Disp.print(output);
        }
        
        //Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}