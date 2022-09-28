package ficha3;
import java.util.*;

public class Ex2 {
    private String brand;
    private String model;
    private int numMessages;
    private int displayX;
    private int displayY;
    private int messageStorage;
    private ArrayList<String> messages;
    private int photoStorage;
    private int appStorage;
    private int photoAndAppStorage;
    private int usedStorage;
    private int numStoredPhotos;
    private int numInstalledApps;
    private ArrayList<String> installedApps;

    public Ex2 () {
        this.brand = "n/a";
        this.model = "n/a";
        this.displayX = 0;
        this.displayY = 0;
        this.numMessages = 0;
        this.messageStorage = 0;
        this.messages = new ArrayList<>(numMessages);
        this.photoStorage = 1024;
        this.appStorage = 2048;
        this.usedStorage = 0;
        this.numStoredPhotos = 0;
        this.numInstalledApps = 0;
        this.installedApps = new ArrayList<>(numInstalledApps);
    }

    public Ex2 (String brand, String model, int dx, int dy, int numMessages, int messageStorage, ArrayList<String> messages, int photoStorage, int appStorage, int usedStorage, int numStoredPhotos, int numInstalledApps, ArrayList<String> installedApps) {
        this.brand = brand;
        this.model = model;
        this.displayX = dx;
        this.displayY = dy;
        this.messageStorage = messageStorage;
        this.messages = new ArrayList<>(numMessages);
        this.numMessages = numMessages;
        this.photoStorage = photoStorage;
        this.appStorage = appStorage;
        this.usedStorage = usedStorage;
        this.numStoredPhotos = numStoredPhotos;
        this.numInstalledApps = numInstalledApps;
        this.installedApps = new ArrayList<>(numInstalledApps);
    }

    public Ex2(Ex2 phone) {
        this.brand = phone.getBrand();
        this.model = phone.getModel();
        this.displayX = phone.getDisplayX();
        this.displayY = phone.getDisplayY();
        this.numMessages = phone.getNumMessages();
        this.messageStorage = phone.getMessageStorage();
        this.photoAndAppStorage = phone.getPhotoAndAppStorage();
        this.messages = new ArrayList<>(phone.getMessages().size());
        this.photoStorage = phone.getPhotoStorage();
        this.appStorage = phone.getAppStorage();
        this.usedStorage = phone.getUsedStorage();
        this.numStoredPhotos = phone.getNumStoredPhotos();
        this.numInstalledApps = phone.getNumInstalledApps();
        this.installedApps = phone.getInstalledApps();
    }

    public String getBrand() {
        return this.brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getModel() {
        return this.model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public int getNumMessages() {
        return this.numMessages;
    }

    public void setNumMessages(int numMessages) {
        this.numMessages = numMessages;
    }

    public int getDisplayX() {
        return this.displayX;
    }

    public void setDisplayX(int displayX) {
        this.displayX = displayX;
    }

    public int getDisplayY() {
        return this.displayY;
    }

    public void setDisplayY(int displayY) {
        this.displayY = displayY;
    }

    public int getMessageStorage() {
        return this.messageStorage;
    }

    public void setMessageStorage(int messageStorage) {
        this.messageStorage = messageStorage;
    }

    public ArrayList<String> getMessages() {
        return this.messages;
    }

    public void setMessages(ArrayList<String> messages) {
        this.messages = new ArrayList<>(messages.size());
        this.messages.addAll(messages);
    }


    public int getPhotoStorage() {
        return this.photoStorage;
    }

    public void setPhotoStorage(int photoStorage) {
        this.photoStorage = photoStorage;
    }

    public int getAppStorage() {
        return this.appStorage;
    }

    public void setAppStorage(int appStorage) {
        this.appStorage = appStorage;
    }

    public int getPhotoAndAppStorage() {
        return this.photoStorage + this.appStorage;
    }

    public void setPhotoAndAppStorage(int photoAndAppStorage) {
        this.photoAndAppStorage = photoAndAppStorage;
    }

    public int getUsedStorage() {
        return this.usedStorage;
    }

    public void setUsedStorage(int usedStorage) {
        this.usedStorage = usedStorage;
    }

    public int getNumStoredPhotos() {
        return this.numStoredPhotos;
    }

    public void setNumStoredPhotos(int numStoredPhotos) {
        this.numStoredPhotos = numStoredPhotos;
    }

    public int getNumInstalledApps() {
        return this.numInstalledApps;
    }

    public void setNumInstalledApps(int numInstalledApps) {
        this.numInstalledApps = numInstalledApps;
    }

    public ArrayList<String> getInstalledApps() {
        return this.installedApps;
    }

    public void setInstalledApps(int numInstalledApps, ArrayList<String> installedApps) {
        this.numInstalledApps = numInstalledApps;
        this.installedApps = new ArrayList<>(numInstalledApps);
        this.installedApps.addAll(installedApps);
    }

    //methods
    public boolean isThereStorage(int numberBytes){
        return numberBytes < (this.photoAndAppStorage - this.usedStorage);
}

    public void installApp (String name, int size) {
        this.numInstalledApps++;
        this.installedApps.add(name);
        this.appStorage += size;
    }

    public void receiveMessage (String message) {
        this.usedStorage += message.length();
        this.messages.add(message);
    }

    public double avgAppSize() {
        return (float) (this.appStorage/this.numInstalledApps);
    }

    public void removeApp(String name, int size) {
        this.appStorage -= size;
        this.numInstalledApps--;
        this.installedApps.remove(name);
    }

    public String biggestMessage() {
        int biggestSize = Integer.MIN_VALUE;
        String answer = "";

        for(String message : this.messages) {
            if(message.length() > biggestSize) {
                biggestSize = message.length();
                answer = message;
            }
        }

        return answer;
    }

    @Override
    public String toString() {
        return "Ex2 {\n" +
                "brand = " + brand + '\n' +
                ", model = " + model + '\n' +
                ", numMessages = " + numMessages + '\n' +
                ", displayX = " + displayX + '\n' +
                ", displayY = " + displayY + '\n' +
                ", messageStorage = " + messageStorage + '\n' +
                ", messages = " + messages + '\n' +
                ", photoStorage = " + photoStorage + '\n' +
                ", appStorage = " + appStorage + '\n' +
                ", photoAndAppStorage = " + photoAndAppStorage + '\n' +
                ", usedStorage = " + usedStorage + '\n' +
                ", numStoredPhotos = " + numStoredPhotos + '\n' +
                ", numInstalledApps = " + numInstalledApps + '\n' +
                ", installedApps = " + installedApps + '\n' +
                '}';
    }
}

