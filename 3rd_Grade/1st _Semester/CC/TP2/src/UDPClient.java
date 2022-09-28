import java.io.File;
import java.io.IOException;
import java.net.*;

public class UDPClient {
        public static void main(String[] args) throws IOException {
                if (new File(args[0]).isDirectory()) {
                        DatagramSocket socket = new DatagramSocket();
                        InetAddress address = InetAddress.getLocalHost();
                        int port = 5252;
                        String inputString = "HELLO";
                        byte[] buf = inputString.getBytes();
                        byte[] buf1 = new byte[5];
                        DatagramPacket dp = new DatagramPacket(buf, 5, address, port);
                        DatagramPacket dptorec = new DatagramPacket(buf1, 5);

                        socket.send(dp);
                        System.out.println("...packet sent successfully....");

                        socket.receive(dptorec);

                        ClientHandler c = new ClientHandler(socket, args[0], InetAddress.getByName(args[1]), dptorec.getPort());
                        c.run();
                }
        }
}
