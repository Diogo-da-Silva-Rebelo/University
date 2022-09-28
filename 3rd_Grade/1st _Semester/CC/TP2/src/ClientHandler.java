import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class ClientHandler implements Manager{
    private final DatagramSocket socket;
    private Map<byte[],String> filestoSend;
    private Map<byte[],FilePacketHandler> filestoReceive;
    private FileListHandler filelist;
    private final String dirName;
    private final InetAddress address;
    private final int port;
    private LogFile lf;


    public ClientHandler(DatagramSocket socket, String dirname, InetAddress address, int port) throws IOException {
        this.socket = socket;
        this.filestoSend = new HashMap<>();
        this.filestoReceive = new HashMap<>();
        this.dirName = dirname;
        this.filelist = new FileListHandler(this.getMyFiles());
        this.address = address;
        this.port = port;
        byte[] p = this.filelist.send(new byte[]{0,0,0,0});
        this.socket.send(new DatagramPacket(p,p.length,this.address,this.port));
        this.lf = new LogFile("log.txt");
    }

    public void run() {
        boolean run = true;
        while (run) {
            try {
                byte[] packet = new byte[1208];
                DatagramPacket dp = new DatagramPacket(packet, 1208,this.address,this.port);
                this.socket.receive(dp);
                System.out.println("Recebi: " + Arrays.toString(packet));

                switch (packet[0]) {
                    case 0 -> {
                        this.lf.logger.fine("Pacote da lista de ficheiros recebido");
                        PacketFileList p = new PacketFileList(packet);
                        byte[] result = this.filelist.append(p);
                        this.socket.send(new DatagramPacket(result,result.length,dp.getAddress(),dp.getPort()));
                    }
                    case 2 -> {
                        this.lf.logger.fine("Recebeu ACK de um pacote da lista de ficheiros");
                        PacketSimple ps = new PacketSimple((byte) 4,packet);
                        byte[] p = this.filelist.send(increasebyte(ps.getIdPacket()));
                        this.socket.send(new DatagramPacket(p,p.length,this.address,this.port));
                    }
                    case 4 -> {
                        this.lf.logger.fine("Recebeu ACK da lista de ficheiros totalmente enviada");
                        this.filestoSend = this.filelist.seeDifferences(0);
                        Map<byte[],String> ftr = this.filelist.seeDifferences(1);
                        for (Map.Entry<byte[],String> f: this.filestoSend.entrySet()){
                            int number = 1;
                            for(int i = 0; i<f.getKey().length; i++){
                                number += f.getKey()[i]*Math.pow(256,f.getKey().length-1-i);
                            }
                            FilePacketHandler fph = new FilePacketHandler(this.lf,this.address,number+1024,f.getKey(),this.dirName,f.getValue(),this.filestoSend.get(f.getKey()));
                            Thread t = new Thread(fph);
                            this.filestoReceive.put(f.getKey(),fph);
                            t.start();
                        }
                        for(Map.Entry<byte[],String> f: ftr.entrySet()){
                            if (this.filestoReceive.get(f.getKey()) == null){
                                int number = 1;
                                for(int i = 0; i<f.getKey().length; i++){
                                    number += f.getKey()[i]*Math.pow(256,f.getKey().length-1-i);
                                }
                                FilePacketHandler fph = new FilePacketHandler(this.lf,this.address,number+1024,f.getKey(),this.dirName,f.getValue(),this.filestoSend.get(f.getKey()));
                                Thread t = new Thread(fph);
                                this.filestoReceive.put(f.getKey(),fph);
                                t.start();
                            }
                        }
                    }
                    case 6 -> {
                        this.lf.logger.warning("Recebeu ACK de erro no envio de pacote da lista de ficheiros");
                        PacketSimple ps = new PacketSimple((byte) 4,packet);
                        byte[] p = this.filelist.send(ps.getIdPacket());
                        this.socket.send(new DatagramPacket(p,p.length,this.address,this.port));
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
                break;
            }
        }
        this.socket.close();
        this.socket.close();
    }

    public String getMyFiles() {
        StringBuilder result = new StringBuilder();
        File folder = new File(this.dirName);
        File[] listOfFiles = folder.listFiles();
        assert listOfFiles != null;
        byte[] id = new byte[]{0,0,0,0};
        for(File f : listOfFiles){
            if (f.isFile())
                result.append(f.getName()).append("%").append(new String(id, StandardCharsets.UTF_8)).append("#");
            id = increasebyte(id);
        }
        return result.toString();
    }
}