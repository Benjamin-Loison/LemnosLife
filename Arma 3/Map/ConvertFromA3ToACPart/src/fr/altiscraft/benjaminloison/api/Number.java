package fr.altiscraft.benjaminloison.api;

public class Number
{
    public static String numberWithSpaces(long nb)
    {
        String nbStr = Long.toString(nb);
        byte base = 3;
        int rest = nbStr.length() % base;
        String nbStrTmp = nbStr.substring(0, rest);
        for(int i = (nbStr.length() - rest) / base; i > 0; i -= 1)
            nbStrTmp += " " + nbStr.substring(nbStr.length() - i * base, nbStr.length() - i * base + base);
        if(rest == 0)
            nbStrTmp = nbStrTmp.replaceFirst(" ", "");
        return nbStrTmp;
    }
}