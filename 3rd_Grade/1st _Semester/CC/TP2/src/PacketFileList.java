import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class PacketFileList extends PacketSimple{
    private boolean finalPacket;
    private String pack;

    public PacketFileList(byte[] packet) {
        super(packet);
        this.finalPacket = packet[5] == (byte) 1;
        this.pack = new String(Arrays.copyOfRange(packet,6,packet.length), StandardCharsets.UTF_8);
    }

    public PacketFileList(String pack, boolean finalpacket){
        super((byte)0);
        this.finalPacket = finalpacket;
        this.pack = pack;
    }

    public boolean isFinalPacket() {
        return finalPacket;
    }

    public String getPack() {
        return pack;
    }

    public byte[] toByte(){
        byte[] result = new byte[6 + this.pack.length()];
        System.arraycopy(super.toByte(),0,result,0,5);
        result[5] = (byte) ((finalPacket) ? 1:0);
        byte[] aux = this.pack.getBytes(StandardCharsets.UTF_8);
        System.arraycopy(aux, 0, result, 6, aux.length);
        return result;
    }

    public String toString() {
        int aux = (finalPacket) ? 1 : 0;
        return super.toString() + aux + pack;
    }
}
