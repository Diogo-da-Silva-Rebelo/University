package CasaInteligente;

public class SmartSpeaker extends SmartDevice{
    private int volume;
    private String channel;
    public static final int MAX = 20;

    public SmartSpeaker(){
        super();
        setVolume(0);
        setChannel("");
    }

    public SmartSpeaker(String ss){
        super(ss);
        setVolume(0);
        setChannel("");
    }

    public SmartSpeaker(int volume, String channel, String sd) {
        super(sd);
        if (volume > 0) setVolume(volume);
        else setVolume(0);
        setChannel(channel);
    }

    public SmartSpeaker(String id, int volume, String channel) {
        super(id);
        this.volume = volume;
        this.channel = channel;
    }

    public SmartSpeaker(String id, boolean state, int volume, String channel) {
        super(id, state);
        this.volume = volume;
        this.channel = channel;
    }

    //getters & setters

    public int getVolume() {
        return this.volume;
    }

    public void setVolume(int volume) {
        this.volume = volume;
    }

    public String getChannel() {
        return this.channel;
    }

    public void setChannel(String channel) {
        this.channel = channel;
    }

    public static int getMAX() {
        return MAX;
    }

    //overrides
    @Override
    public boolean equals(Object o) {
        return super.equals(o);
    }

    //methods
    public void volumeUP(){
        if (this.volume < MAX) setVolume(this.volume++);
    }

    public void volumeDOWN(){
        if (this.volume > 0) setVolume(this.volume--);
    }
}
