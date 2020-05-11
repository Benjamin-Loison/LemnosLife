import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Time.initializeTimer();
        HashMap<String, ArrayList<String>> map = new HashMap<String, ArrayList<String>>();
        File file = new File("data.csv");
        try
        {
            Scanner scanner = new Scanner(file);
            while(scanner.hasNextLine())
            {
                String line = scanner.nextLine(), lineParts[] = line.split(","), email = "email";
                if(lineParts.length >= 3)
                    email = lineParts[2];
                String username = lineParts[0];
                double amount = Double.parseDouble(lineParts[1]);
                if(map.containsKey(username))
                {
                    ArrayList<String> valueString = map.get(username);
                    boolean bool = false;
                    for(int i = 0; i < valueString.size(); i++)
                    {
                        String string = valueString.get(i);
                        String[] stringPartStrings = string.split(" ");
                        if(stringPartStrings[0] == email)
                        {
                            valueString.set(i, stringPartStrings[0] + " " + (Double.parseDouble(stringPartStrings[1]) + amount));
                            bool = true;
                            break;
                        }
                    }
                    if(!bool)
                    {
                        valueString.add(email + " " + amount);
                    }
                    map.put(username, valueString);
                }
                else
                {
                    ArrayList<String> arrayList = new ArrayList<String>();
                    arrayList.add(email + " " + amount);
                    map.put(username, arrayList);
                }
            }
            scanner.close();
            Iterator<String> iterator = map.keySet().iterator();
            while(iterator.hasNext())
            {
                String username = iterator.next(), bestEmail = "email";
                double bestEmailAmount = 0, totalAmount = 0;
                ArrayList<String> valueString = map.get(username);
                HashMap<String, Double> user = new HashMap<String, Double>();
                for(int i = 0; i < valueString.size(); i++)
                {
                    String[] parts = valueString.get(i).split(" ");
                    double amount = Double.parseDouble(parts[1]);
                    if(user.containsKey(parts[0]))
                        user.put(parts[0], amount + user.get(parts[0]));
                    else
                        user.put(parts[0], amount);
                }
                Iterator<String> it = user.keySet().iterator();
                while(it.hasNext())
                {
                    String email = it.next();
                    //if(email.equals("email")) continue;
                    double amount = user.get(email);
                    //Disp.print(amount);
                    if(amount > bestEmailAmount/* && !email.equals("email")*/) // PATCH FAULT
                    {
                        bestEmailAmount = amount;
                        bestEmail = email;
                    }
                    totalAmount += amount;
                }
                if(bestEmail.equals("email")) 
                    continue;
                Disp.print(username + " " + bestEmail + " " + (totalAmount * 100 + "").replace(".0", ""));
            }
        }
        catch(Exception exception)
        {
            exception.printStackTrace();
        }
        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
    }
}