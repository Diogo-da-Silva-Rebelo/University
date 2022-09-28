import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class PacketFile extends PacketSimple implements Manager {
    private boolean finalPacket;
    private byte[] idFile;
    private String pack;

    public PacketFile(byte[] packet) {
        super(packet);
        this.finalPacket = packet[5] == 1;
        this.idFile = Arrays.copyOfRange(packet, 6, 8);
        this.pack = new String(Arrays.copyOfRange(packet,8,packet.length), StandardCharsets.UTF_8).replaceAll(String.valueOf((byte)0),"");
    }

    public boolean isFinalPacket() {
        return finalPacket;
    }

    public String getPack() {
        return pack;
    }

    public byte[] toByte(){
        byte[] result = new byte[8 + this.pack.length()];
        result[0] = (byte) 1;
        byte[] aux = this.getIdPacket();
        System.arraycopy(aux, 0, result, 1, aux.length);
        result[5] = (byte) (finalPacket ? 1:0);
        aux = this.idFile;
        System.arraycopy(aux,0,result,6,aux.length);
        aux = this.pack.getBytes(StandardCharsets.UTF_8);
        System.arraycopy(aux,0,result,8,aux.length);
        return result;
    }

    public String toString(){
        int aux = (finalPacket) ? 1 : 0;
        return super.toString() + aux + new String(this.idFile,StandardCharsets.UTF_8) + this.pack;
    }
}
