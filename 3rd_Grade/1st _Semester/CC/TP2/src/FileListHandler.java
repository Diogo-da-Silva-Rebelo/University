import java.nio.charset.StandardCharsets;
import java.util.*;

public class FileListHandler implements Manager{
    private String filelistRECEIVED;
    private String myfiles;
    private byte[] currentIDsent;
    private byte[] idtoRECEIVE;
    private boolean completed;


    public FileListHandler(String myfiles){
        this.filelistRECEIVED = "";
        this.myfiles = myfiles;
        this.currentIDsent = new byte[]{0,0,0,0};
        this.idtoRECEIVE = new byte[]{0,0,0,0};
        this.completed = false;
    }

    public String getMyfiles() {
        return myfiles;
    }

    public byte[] send(byte[] packetToSend){
        int number = 1;
        for(int i = 0; i<packetToSend.length; i++){
            number += packetToSend[i]*Math.pow(256,packetToSend.length-1-i);
        }
        String send = (myfiles.length() > number * 1200) ? myfiles.substring((number-1)*1200,number * 1200):myfiles.substring((number-1)*1200);
        boolean finalpacket = myfiles.length() <= number * 1200;

        return new PacketFileList(send,finalpacket).toByte();
    }

    public byte[] append(PacketFileList packet){
        byte[] result = new byte[5];
        System.arraycopy(this.idtoRECEIVE,0,result,1,this.idtoRECEIVE.length);
        if (Arrays.equals(packet.getIdPacket(),this.idtoRECEIVE)){
            this.filelistRECEIVED += repairString(packet.getPack());

            this.idtoRECEIVE = increasebyte(this.idtoRECEIVE);
            this.completed = packet.isFinalPacket();

            if (this.completed) result[0] = 4;
            else result[0] = 2;
        }
        else result[0] = 6;
        return result;
    }

    //caso seja 0, e para ver os que envio, caso seja 1, e para ver os que recebo
    public Map<byte[],String> seeDifferences(int option){
        Map<byte[],String> toSend = new HashMap<>();
        Map<String,String> serverFiles = this.fillMap(this.filelistRECEIVED);
        Map<String,String> myFiles = this.fillMap(this.myfiles);
        List<String> differences = new ArrayList<>();
        if (option == 0){
            differences.addAll(myFiles.keySet());
            differences.removeAll(new ArrayList<>(serverFiles.keySet()));
            for(String file : differences){
                toSend.put(myFiles.get(file).getBytes(StandardCharsets.UTF_8),file); //Aqui troca. Antes o Map tinha Nome,ID e agora tem ID,Nome
            }
        }
        else{
            differences.addAll(serverFiles.keySet());
            differences.removeAll(new ArrayList<>(myFiles.keySet()));
            for(String file : differences){
                toSend.put(serverFiles.get(file).getBytes(StandardCharsets.UTF_8),file); //Aqui troca. Antes o Map tinha Nome,ID e agora tem ID,Nome
            }
        }
        return toSend;
    }

    public Map<String,String> fillMap(String file){
        Map<String,String> result = new HashMap<>();
        ArrayList<String> list = new ArrayList<>(Arrays.asList(file.split("#")));
        for (String element : list){
            if(element.contains("%")) {
                String[] aux = element.split("%");
                result.put(aux[0], aux[1]);
            }
        }
        return result;
    }
}
