package PraticaTestes.Teste17;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server{
    public static void main (String [] args){
        try{
            ServerSocket socket = new ServerSocket(12345);
            ControladorTemp controlador = new ControladorTemp(14,19,true);
            while(true){
                Socket cs = socket.accept();
                System.out.println("Connection Accepted!!");
                Thread t = new Thread( new ClientHandler (cs,controlador));
                t.start();
            }
        } catch(IOException e){
            e.printStackTrace();
        }
    }
}