package DriveIt;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

public class Veiculo {
    private String registration;
    private String brand;
    private String model;
    private int year;
    private double speedPerKm;
    private double teoricPricePerKm;
    private List<Integer> rank;
    private double kms;
    private double lastRideKms;
    private double realCostPerKm;

    public double realCostPerKm(){
        return (this.teoricPricePerKm * 1.1);
    }

    public int rank(){
        try {
            return (int) this.rank.stream()
                    .mapToInt(Integer::intValue).average().getAsDouble();
        }
        catch (NoSuchElementException e) {
            return -1;
        }
    }

    public Veiculo() {
        this.registration = "";
        this.brand = "";
        this.model = "";
        this.year = 0;
        this.speedPerKm = 0;
        this.teoricPricePerKm = 0;
        this.rank = new ArrayList<>();
        this.kms = 0;
        this.lastRideKms = 0;
        this.realCostPerKm = 0;
    }

    public Veiculo(String registration, String brand, String model, int year, double speedPerKm, double teoricPricePerKm, ArrayList<Integer> rank, double kms, double lastRideKms, double realCostPerKm) {
        this.registration = registration;
        this.brand = brand;
        this.model = model;
        this.year = year;
        this.speedPerKm = speedPerKm;
        this.teoricPricePerKm = teoricPricePerKm;
        this.rank = new ArrayList<>(rank);
        this.kms = kms;
        this.lastRideKms = lastRideKms;
        this.realCostPerKm = realCostPerKm;
    }

    public Veiculo(Veiculo v){
        this.brand = v.getBrand();
        this.model = v.getModel();
        this.registration= v.getRegistration();
        this.year = v.getYear();
        this.speedPerKm = v.getSpeedPerKm();
        this.teoricPricePerKm = v.getTeoricPricePerKm();
        this.rank = v.getRank();
        this.kms = v.getKms();
        this.lastRideKms = v.getLastRideKms();
        this.realCostPerKm = v.getRealCostPerKm();
    }

    public String getRegistration() {
        return this.registration;
    }

    public void setRegistration(String registration) {
        this.registration = registration;
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

    public int getYear() {
        return this.year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public double getSpeedPerKm() {
        return this.speedPerKm;
    }

    public void setSpeedPerKm(double speedPerKm) {
        this.speedPerKm = speedPerKm;
    }

    public double getTeoricPricePerKm() {
        return this.teoricPricePerKm;
    }

    public void setTeoricPricePerKm(double teoricPricePerKm) {
        this.teoricPricePerKm = teoricPricePerKm;
    }

    public List<Integer> getRank() {
        return new ArrayList<>(this.rank);
    }

    public void setRank(ArrayList<Integer> rank) {
            this.rank = rank;
    }

    public double getKms() {
        return this.kms;
    }

    public void setKms(double kms) {
        this.kms = kms;
    }

    public double getLastRideKms() {
        return this.lastRideKms;
    }

    public void setLastRideKms(double lastRideKms) {
        this.lastRideKms = lastRideKms;
    }

    public double getRealCostPerKm() {
        return this.realCostPerKm;
    }

    public void setRealCostPerKm(double realCostPerKm) {
        this.realCostPerKm = realCostPerKm;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Veiculo veiculo = (Veiculo) o;
        return this.registration.equals(veiculo.registration) &&
                this.brand.equals(veiculo.brand) &&
                this.model.equals(veiculo.model) &&
                this.year == veiculo.year &&
                this.speedPerKm == veiculo.speedPerKm &&
                this.teoricPricePerKm == veiculo.teoricPricePerKm &&
                this.rank.equals(veiculo.rank);
    }


    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    @Override
    public String toString() {
        return "Veiculo {\n" +
                "\tregistration = " + registration +  "\n" +
                "\tbrand = " + brand +  "\n" +
                "\tmodel = " + model +  "\n" +
                "\tyear = " + year +  "\n" +
                "\tspeedPerKm = " + speedPerKm +  "\n" +
                "\tteoricPricePerKm = " + teoricPricePerKm +  "\n" +
                "\trank = " + rank + "\n" +
                "\tkms = " + kms + "\n" +
                "\tlastRideKms = " + lastRideKms + "\n" +
                "\trealCostPerKm = " + realCostPerKm + "\n" +
                '}' + "\n";
    }

    public int compareTo(Veiculo v){
        if (this.brand.compareTo(v.getBrand()) == 0)
            return (this.model.compareTo((v.getModel())));
        else
            return (this.brand.compareTo((v.getBrand())));
    }

    public void addKms(double kms){
        this.kms += kms;
        this.lastRideKms = kms;
    }
}
