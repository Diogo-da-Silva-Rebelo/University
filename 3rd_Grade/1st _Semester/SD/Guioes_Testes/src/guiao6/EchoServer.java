package guiao6;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

//versão sequencial
public class EchoServer {

    public static void main(String[] args) {
        try {
            //Abrir porta de entrada
            ServerSocket ss = new ServerSocket(12345);

            while (true) {
                //desbloquear, para receber novo client
                Socket socket = ss.accept();

                //Semelhante a readLine
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                //Escreve o que conseguir
                PrintWriter out = new PrintWriter(socket.getOutputStream());

                String line;
                int sum = 0;
                int count = 0;
                float avg;
                //!=null -> enquanto não atingir o EOF
                while ((line = in.readLine()) != null) {
                    sum += Integer.parseInt(line);
                    count++;

                    out.println(sum);
                    out.flush();
                }

                avg = (float) sum / count;
                out.println(avg);
                out.flush();

                //fechar extremidades
                socket.shutdownOutput();
                socket.shutdownInput();
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}