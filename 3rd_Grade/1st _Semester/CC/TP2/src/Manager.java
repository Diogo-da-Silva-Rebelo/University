public interface Manager {
    default byte[] increasebyte(byte[] currentID){
            if (currentID[3] == (byte)255){
                if (currentID[2] == (byte)255){
                    if (currentID[1] == (byte)255) {
                        if (currentID[0] == (byte)255) currentID = new byte[]{0,0,0,0};
                        else currentID[0] += 1;
                    }
                    else currentID[1] += 1;
                }
                else currentID[2] += 1;
            }
            else currentID[3] += 1;
            return currentID;
        }

    default String repairString(String pack) {
        int index = pack.lastIndexOf("#");
        if (index <= pack.length()-1){
            if (pack.charAt(index + 1) == (byte)0) {
                return pack.substring(0,index+1);
            }
        }
        return pack;
    }
}
