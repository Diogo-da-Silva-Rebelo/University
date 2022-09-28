import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Arrays;

public class FilePacketHandler implements Runnable,Manager {
    private DatagramSocket socket;
    private InetAddress itsAddress;
    private int port;
    private byte[] idFile;
    private byte[] idtoRECEIVE;
    private ArrayList<String> received;
    private ArrayList<byte[]> sent;
    private String fileRECEIVE;
    private String fileSEND;
    private FileInputStream fileInputStream;
    private int filelength;
    private boolean filesent;
    private boolean filereceived;
    private LogFile lf;

    public FilePacketHandler(LogFile lf, InetAddress itsAddress, int port, byte[] idFile, String folder, String fileRECEIVE, String fileSEND) throws IOException {
        this.socket = new DatagramSocket(port);
        this.itsAddress = itsAddress;
        this.port = port;
        this.idFile = idFile;
        this.idtoRECEIVE = new byte[]{0,0,0,0};
        this.received = new ArrayList<>();
        this.sent = new ArrayList<>();
        this.fileRECEIVE = fileRECEIVE;
        this.filereceived = this.fileRECEIVE == null;
        this.lf = lf;

        if (fileSEND != null){
            this.fileSEND = folder + File.separator + fileSEND;
            byte[] send = this.createPacket(new byte[]{0,0,0,0});
            this.socket.send(new DatagramPacket(send,send.length,this.itsAddress,this.port));
            this.filesent = false;
        }
        else {
            this.fileSEND = null;
            this.filesent = true;
        }
    }

    @Override
    public void run() {
        boolean run = true;
        while (run) {
            try {
                byte[] packet = new byte[1208];
                DatagramPacket dp = new DatagramPacket(packet, 1208,this.itsAddress,this.port);
                this.socket.receive(dp);

                switch (packet[0]) {
                    case 1 -> {
                        this.lf.logger.fine("Pacote de um ficheiro recebido");
                        PacketFile pf = new PacketFile(packet);
                        byte[] send = this.append(pf);
                        DatagramPacket dps = new DatagramPacket(send,send.length,this.itsAddress,this.port);
                        this.socket.send(dps);
                    }
                    case 3 -> {
                        this.lf.logger.fine("Recebeu ACK de um pacote de um ficheiro");
                        byte[] send = createPacket(increasebyte(Arrays.copyOfRange(packet,1,5)));
                        DatagramPacket dps = new DatagramPacket(send,send.length,this.itsAddress,this.port);
                        this.socket.send(dps);
                        this.filereceived = true;
                        if (this.filesent)
                            run = false;
                    }
                    case 5 -> {
                        this.lf.logger.fine("Recebeu ACK de um ficheiro totalmente enviado");
                        this.filesent = true;
                        if(this.filereceived)
                            run = false;
                    }
                    case 7 -> {
                        this.lf.logger.warning("Recebeu ACK de erro no envio de pacote de um ficheiro");
                        byte[] send = this.createPacket(Arrays.copyOfRange(packet,1,packet.length));
                        this.socket.send(new DatagramPacket(send,send.length,this.itsAddress,this.port));
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
                break;
            }
        }
        this.socket.close();
    }

    public byte[] append(PacketFile packet) throws IOException {
        byte[] result = new byte[9];

        if (Arrays.equals(packet.getIdPacket(),this.idtoRECEIVE)){
            this.received.add(packet.getPack());

            if (packet.isFinalPacket()) {
                result[0] = 5;
                System.arraycopy(this.idFile, 0, result, 1, this.idFile.length);
                this.writeToFile();
            }
            else {
                result[0] = 3;
                System.arraycopy(this.idtoRECEIVE, 0, result, 1, this.idtoRECEIVE.length);
            }
            this.idtoRECEIVE = increasebyte(this.idtoRECEIVE);
        }
        else {
            result[0] = 7;
            System.arraycopy(this.idtoRECEIVE,0,result,1,this.idtoRECEIVE.length);
            System.arraycopy(this.idFile, 0, result, 5, this.idFile.length);
        }
        return result;
    }

    public void writeToFile(){
        try {
            FileWriter fw = new FileWriter(this.fileRECEIVE, true);
            BufferedWriter bw = new BufferedWriter(fw);
            for(String e : this.received){
                bw.write(e);
            }
            bw.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    public byte[] createPacket(byte[] idtoSend) throws IOException {
        int number = 0;
        for (int i = 0; i < idtoSend.length; i++) {
            number += idtoSend[i] * Math.pow(256, idtoSend.length - 1 - i);
        }
        if (number >= this.sent.size()) {
            this.fileInputStream = new FileInputStream(this.fileSEND);
            byte[] file = new byte[1200];
            int nread = Math.min(1200 * (number + 1), this.filelength);
            int read = this.fileInputStream.read(file, 1200 * number, nread);
            this.fileInputStream.close();
            byte[] result = new byte[1208];
            if (read < 1200) result[5] = 1;
            else result[5] = 0;
            result[0] = 1;
            System.arraycopy(this.idtoRECEIVE, 0, result, 1, 4);
            System.arraycopy(this.idFile, 0, result, 6, 2);
            System.arraycopy(file, 0, result, 7, file.length);
            this.sent.add(result);
            return result;
        }
        else{
            return this.sent.get(number);
        }
    }
}
