import java.io.*;
import java.net.*;


public class UDPServer {
    public void run(String dirname, String ip) throws IOException {
        if (new File(dirname).isDirectory()) {
            DatagramSocket ds = new DatagramSocket(5252);
            byte[] buf = new byte[5];
            String inputString = "HELLO";
            byte[] send = inputString.getBytes();
            //byte send[] = { 13, 18 };
            DatagramPacket dp = new DatagramPacket(buf, 5);

            ds.receive(dp);
            System.out.println("Received packet data : " +
                    new String(dp.getData()));

            System.out.println(dp.getAddress() + "  " + dp.getPort());

            DatagramPacket senddp = new DatagramPacket(send, 5,
                    dp.getAddress(), dp.getPort());

            DatagramSocket socket = new DatagramSocket();
            socket.send(senddp);

            ClientHandler c = null;
            try {
                c = new ClientHandler(socket, dirname, InetAddress.getByName(ip), dp.getPort());
            } catch (IOException e) {
                e.printStackTrace();
            }
            c.run();
        }
    }
}
