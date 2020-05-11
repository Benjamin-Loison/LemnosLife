import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        Disp.initializeLogger();
        Time.initializeTimer();

        try
        {
            Scanner scanner = new Scanner(System.in);
            Disp.print("IP/Domain: ");
            String ipDomainString = scanner.nextLine();
            Disp.print(ipDomainString);
            Disp.print("Port: ");
            int port = scanner.nextInt();
            Disp.print(port);

            //Disp.log = false;

            Socket sock = new Socket(ipDomainString, port);

            
            BufferedInputStream bis = new BufferedInputStream(sock.getInputStream());
            
            Thread th = new Thread()
            {
                public void run()
                {
                    try
                    {
                        while(true)
                        {
                            String content = "";
                            int stream;
                            byte[] b = new byte[1000000];
                            while((stream = bis.read(b)) != -1)
                                content += new String(b, 0, stream);
                            Disp.print(content);
                        }
                    }
                    catch(Exception e)
                    {
                        e.printStackTrace();
                    }
                }
            };
            th.start();

            while(true)
            {
                BufferedOutputStream bos = new BufferedOutputStream(sock.getOutputStream());
                String request = scanner.nextLine();
                if(request.equals("exit"))
                    break;
                Disp.print(request);

                bos.write((request + "#").getBytes());
                bos.flush();
            }

            scanner.close();
            sock.close();
            // th.interrupt(); // ?
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }

        Disp.print("Work finished in " + Time.getExecuteTimeInMs() + " ms !");
        Disp.closeLogger();
    }
}