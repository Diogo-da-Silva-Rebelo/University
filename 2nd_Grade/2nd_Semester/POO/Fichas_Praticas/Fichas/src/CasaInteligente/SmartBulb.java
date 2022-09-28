package CasaInteligente;

public class SmartBulb extends SmartDevice{
    private int tone;
    public static final int WARM = 2;
    public static final int NEUTRAL = 1;
    public static final int COLD = 0;

    //constructors
    public SmartBulb() {
        super();
        setTone(NEUTRAL);
    }

    public SmartBulb(String sb){
        super(sb);
        setTone(NEUTRAL);
    }

    public SmartBulb(String sb, int tone){
        super(sb);
        this.tone = tone;
    }

    //getters & setters
    public int getTone() {
        return this.tone;
    }

    public void setTone(int tone) {
        if (tone >= WARM) setTone(WARM);
        else if (tone <= COLD) setTone(COLD);
        else setTone(NEUTRAL);
    }

    //overrides
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof SmartBulb)) return false;
        SmartBulb smartBulb = (SmartBulb) o;
        return getTone() == smartBulb.getTone();
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
