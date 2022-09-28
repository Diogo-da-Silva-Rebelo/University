package CasaInteligente;

import java.util.Objects;

public class SmartDevice {
    private String id;
    private boolean state;
    //state = FALSE -> OFF (turned off)
    //state = TRUE -> ON (turned on)

    //constructors
    public SmartDevice(){
        setId("");
        setState(false);
    }

    public SmartDevice (SmartDevice sm){
        setId(sm.getId());
        setState(sm.getState());
    }
    public SmartDevice(String id){
        setId(id);
        setState(false);
    }

    public SmartDevice(String id, boolean state) {
        setId(id);
        setState(state);
    }

    //getters & setters
    public String getId() {
        return this.id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public boolean getState() {
        return this.state;
    }

    public void setState(boolean state) {
        this.state = state;
    }

    public void setON(boolean state){
        this.setState(state);
    }

    public boolean getON(){
        return this.getState();
    }

    //overrides
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof SmartDevice)) return false;
        SmartDevice that = (SmartDevice) o;
        return getState() == that.getState() && Objects.equals(getId(), that.getId());
    }

    public SmartDevice clone(){
        return new SmartDevice(this);
    }
}
