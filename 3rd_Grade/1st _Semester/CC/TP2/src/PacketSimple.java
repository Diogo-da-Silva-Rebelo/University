import java.nio.charset.StandardCharsets;
import java.util.Arrays;

//serve para mandar aqueles ACKs
public class PacketSimple {
    private byte first;
    private byte[] idPacket; //4 bytes

    public PacketSimple(byte first){
        this.first = first;
        this.idPacket = new byte[]{0,0,0,0};
    }

    public PacketSimple(byte[] packet) {
        this.first = packet[0];
        this.idPacket = Arrays.copyOfRange(packet, 1, 5);
    }

    public PacketSimple(byte first, byte[] packet) {
        this.first = first;
        this.idPacket = Arrays.copyOfRange(packet, 1, 5);
    }

    public byte[] getIdPacket() {
        return this.idPacket;
    }

    public byte[] toByte(){
        byte[] result = new byte[5];
        result[0] = this.first;
        byte[] aux = this.idPacket;
        System.arraycopy(aux, 0, result, 1, aux.length);
        return result;
    }

    public String toString() {
        return this.first + new String(idPacket, StandardCharsets.UTF_8);
    }
}
