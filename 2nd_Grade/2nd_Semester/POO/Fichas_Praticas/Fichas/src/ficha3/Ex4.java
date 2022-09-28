package ficha3;

public class Ex4 {
    private Ex4LampState state;
    private double powerNormal;
    private double powerEco;

    public Ex4() {
        this.state = Ex4LampState.OFF;
        this.powerNormal = 0;
        this.powerEco = 0;
    }

    public Ex4(double powerNormal, double powerEco, Ex4LampState state) {
        this.state = state;
        this.powerNormal = powerNormal;
        this.powerEco = powerEco;
    }

    public Ex4(Ex4 lamp) {
        this.state = lamp.getState();
        this.powerNormal = lamp.getPowerNormal();
        this.powerEco = lamp.getPowerEco();
    }

    public Ex4LampState getState() {
        return this.state;
    }

    public void setState(Ex4LampState state) {
        this.state = state;
    }

    public double getPowerNormal() {
        return this.powerNormal;
    }

    public void setPowerNormal(double powerNormal) {
        this.powerNormal = powerNormal;
    }

    public double getPowerEco() {
        return this.powerEco;
    }

    public void setPowerEco(double powerEco) {
        this.powerEco = powerEco;
    }

    public void lampON() {
        this.state = Ex4LampState.ON;
    }

    public void lampECO() {
        this.state = Ex4LampState.ECO;
    }

    public double consume (){
        return (getPowerEco() + getPowerNormal());
    }

    public String toString() {
        final StringBuffer sb = new StringBuffer("Lamp {");
        sb.append("\tState = ").append(this.state.toString()).append("\n");
        sb.append("\tNormal power = ").append(this.powerNormal).append("W\n}");
        sb.append("\tEco power = ").append(this.powerEco).append("W\n}");
        return sb.toString();
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        Ex4 lamp = (Ex4) o;
        return this.state.equals(lamp.getState()) &&
                Double.compare(lamp.getPowerNormal(), this.powerNormal) == 0 &&
                Double.compare(lamp.getPowerEco(), this.powerEco) == 0;
    }

    public Ex4 clone() {
        return new Ex4(this);
    }
}