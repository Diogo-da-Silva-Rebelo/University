package Entidades.API;

import com.fasterxml.jackson.annotation.JsonInclude;

import java.util.List;

@JsonInclude(JsonInclude.Include.NON_NULL)
public class Bookmaker {
    private String key;
    private String lastUpdate;
    private List<Market> markets;

    public Bookmaker(){
        this.key = null;
        this.lastUpdate = null;
        this.markets = null;
    }

    public Bookmaker(String key, String lastUpdate, List<Market> markets) {
        this.key = key;
        this.lastUpdate = lastUpdate;
        this.markets = markets;
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public String getLastUpdate() {
        return lastUpdate;
    }

    public void setLastUpdate(String lastUpdate) {
        this.lastUpdate = lastUpdate;
    }

    public List<Market> getMarkets() {
        return markets;
    }

    public void setMarkets(List<Market> markets) {
        this.markets = markets;
    }

    @Override
    public String toString() {
        return "Bookmaker{" +
                "key='" + key + '\'' +
                ", lastUpdate='" + lastUpdate + '\'' +
                ", markets=" + markets +
                '}';
    }
}