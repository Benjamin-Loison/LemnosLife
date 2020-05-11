import java.util.Calendar;
import java.util.Date;

public class Time
{
    private static long beginTime;

    public static String getTimeFormatted()
    {
        Calendar cal = Calendar.getInstance();
        return "[" + cal.get(Calendar.HOUR) + ":" + cal.get(Calendar.MINUTE) + ":" + cal.get(Calendar.SECOND) + "]";
    }

    public static void initializeTimer()
    {
        beginTime = new Date().getTime();
        Disp.print("Time's launched !");
    }

    public static long getExecuteTimeInMs()
    {
        return new Date().getTime() - beginTime;
    }
}
