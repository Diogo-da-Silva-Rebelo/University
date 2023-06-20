package Entidades.API;

import com.fasterxml.jackson.annotation.JsonInclude;

@JsonInclude(JsonInclude.Include.NON_NULL)
public class Outcome {
    private String name;
    private int price;

    public Outcome(){
        this.name = null;
        this.price = 0;
    }

    public Outcome(String name, int price) {
        this.name = name;
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public String toString() {
        return "Outcome{" +
                "name='" + name + '\'' +
                ", price=" + price +
                '}';
    }

    public void setPrice(int price) {
        this.price = price;
    }
}