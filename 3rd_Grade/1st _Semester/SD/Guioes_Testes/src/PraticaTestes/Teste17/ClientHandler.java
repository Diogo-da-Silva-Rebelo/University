package PraticaTestes.Teste17;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientHandler implements Runnable {
    private Socket cs;
    private ControladorTemp controlador;

    public ClientHandler(Socket cs, ControladorTemp controlador) {
        this.cs = cs;
        this.controlador = controlador;
    }

    @Override
    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(cs.getInputStream()));
            PrintWriter out = new PrintWriter(this.cs.getOutputStream(), true);
            while (in.readLine() != null) {
                String request = in.readLine();
                String[] args = request.trim().split("\\s*");
                String action = args[0];

                int temp;
                boolean bool;

                switch (action) {
                    case "temperatura" -> {
                        temp = Integer.parseInt(args[1]);
                        this.controlador.temperatura(temp);
                        out.println("Temperatura Atual: " + temp);
                    }
                    case "limiar" -> {
                        temp = Integer.parseInt(args[1]);
                        this.controlador.limiar(temp);
                        out.println("Limiar Atual: " + temp);
                    }
                    case "on_off" -> {
                        bool = Boolean.parseBoolean(args[1]);
                        this.controlador.on_off(bool);
                        out.println("Estado da caldeira: " + (!bool));
                    }
                    default -> out.println("Operação Inválida.");
                }
                System.out.println("Connection Closed!");
                this.cs.shutdownOutput();
                this.cs.shutdownInput();
                this.cs.close();
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}