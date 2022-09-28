import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer implements Runnable {
    public void run() {

        ServerSocket ss = null;
        try {
            ss = new ServerSocket(8080);
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("Listening for connection on port 8080 ....");

        while (true) {
            Socket client = null;
            try {
                client = ss.accept();
                TCPClientHandler tcpch = new TCPClientHandler(client);
                Thread t = new Thread(tcpch);
                t.start();
            } catch (Exception e) {
                assert client != null;
                try {
                    client.close();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
                e.printStackTrace();
            }
        }
    }

    private static class TCPClientHandler implements Runnable {
        private final Socket clientSocket;

        public TCPClientHandler(Socket socket) {
            this.clientSocket = socket;
        }

        public void run() {
            try {
                System.out.println(Thread.currentThread() + " New client connected " + clientSocket.getInetAddress().getHostAddress());
                InputStream in = clientSocket.getInputStream();
                OutputStream out = clientSocket.getOutputStream();
                String html = "<html><head><title>Simple Java HTTP Server</title></head><body><h1>Servidor a correr</h1></body></html>";
                String CRLF = "\n\r";
                String response = "HTTP/1.1 200 OK" + CRLF +
                        "Content-Length: " + html.getBytes().length + CRLF +
                        CRLF +
                        html +
                        CRLF + CRLF;

                out.write(response.getBytes());
                in.close();
                out.close();
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}