import java.io.IOException;

public class Server {
    public static void main(String[] args) throws IOException {
        TCPServer tcps = new TCPServer();
        Thread t = new Thread(tcps);
        t.start();
        UDPServer udps = new UDPServer();
        udps.run(args[0],args[1]);
    }
}
