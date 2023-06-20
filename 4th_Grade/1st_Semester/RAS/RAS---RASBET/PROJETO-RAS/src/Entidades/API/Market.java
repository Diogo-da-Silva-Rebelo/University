package Entidades.API;

import com.fasterxml.jackson.annotation.JsonInclude;

import java.util.List;

@JsonInclude(JsonInclude.Include.NON_NULL)
public class Market {
    private String key;
    private List<Outcome> outcomes;

    public Market(){
        this.key = null;
        this.outcomes = null;
    }

    public Market(String key, List<Outcome> outcomes) {
        this.key = key;
        this.outcomes = outcomes;
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public List<Outcome> getOutcomes() {
        return outcomes;
    }

    @Override
    public String toString() {
        return "Market{" +
                "key='" + key + '\'' +
                ", outcomes=" + outcomes +
                '}';
    }

    public void setOutcomes(List<Outcome> outcomes) {
        this.outcomes = outcomes;
    }
}