import java.util.ArrayList;

public class ArrayListAPI
{
    public static ArrayList<String> getArrayListString(ArrayList<Integer> integerArray)
    {
        ArrayList<String> stringArray = new ArrayList<String>();
        for(int nb : integerArray)
            stringArray.add(nb + "");
        return stringArray;
    }
}