package guiao6;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

//Versão com concorrência

class Registo {
        private int sum = 0;
        private int n = 0;

        public void sum(int value){
            //lock
            sum += value;
            //unlock
        }

        public double avg(){
            //lock
            return (double) sum/n;
            //unlock
        }
}

class ClientHandler implements Runnable {
    private final Socket client;
    private final Registo reg;

    public ClientHandler(Socket client, Registo r) {
        this.client = client;
        this.reg = r;
    }

    @Override
    public void run() {
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
                int value = 0;
                //!=null -> enquanto não atingir o EOF
                while ((line = in.readLine()) != null) {
                    value = Integer.parseInt(line);
                    sum += value;
                    reg.sum(value);

                    out.println(sum);
                    out.flush();
                }
                out.println(reg.avg());
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

public class EchoServerv2 {

    public static void main(String[] args) {

        Registo r = new Registo();

        try {
            ServerSocket ss = new ServerSocket(12345);

            while (true) {
                //desbloquear, para receber novo client
                Socket socket = ss.accept();
                new Thread(new ClientHandler(socket,r)).start();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
