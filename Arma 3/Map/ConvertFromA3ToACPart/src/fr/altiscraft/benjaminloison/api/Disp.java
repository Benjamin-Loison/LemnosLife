package fr.altiscraft.benjaminloison.api;

public class Disp
{
    public static void print(Object obj)
    {
        System.out.println(Time.getTimeFormatted() + " " + obj.toString());
    }
    
    public static void print(Object obj, boolean exit)
    {
        print(obj);
        print("/!\\ Add -f to force removing existing files /!\\");
        print("This was a fatal error and the software must stop, sorry...");
        if(exit)
            System.exit(0);
    }
}