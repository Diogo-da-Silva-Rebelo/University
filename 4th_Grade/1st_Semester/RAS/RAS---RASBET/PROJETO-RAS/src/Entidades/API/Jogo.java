package Entidades.API;

import com.fasterxml.jackson.annotation.JsonInclude;

import java.util.List;

@JsonInclude(JsonInclude.Include.NON_NULL)
public class Jogo {
    private String id;
    private String homeTeam;
    private String awayTeam;
    private String commenceTime;
    private Boolean completed;
    private String scores;
    private List<Bookmaker> bookmakers;
    private String progCorreto;

    public Jogo(){
        this.id = null;
        this.homeTeam = null;
        this.awayTeam = null;
        this.commenceTime = null;
        this.completed = null;
        this.scores = null;
        this.bookmakers = null;
    }

    public Jogo(String id, String homeTeam, String awayTeam, String commenceTime, Boolean completed, String scores, List<Bookmaker> bookmakers) {
        this.id = id;
        this.homeTeam = homeTeam;
        this.awayTeam = awayTeam;
        this.commenceTime = commenceTime;
        this.completed = completed;
        this.scores = scores;
        this.bookmakers = bookmakers;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getHomeTeam() {
        return homeTeam;
    }

    public void setHomeTeam(String homeTeam) {
        this.homeTeam = homeTeam;
    }

    public String getAwayTeam() {
        return awayTeam;
    }

    public void setAwayTeam(String awayTeam) {
        this.awayTeam = awayTeam;
    }

    public String getCommenceTime() {
        return commenceTime;
    }

    public void setCommenceTime(String commenceTime) {
        this.commenceTime = commenceTime;
    }

    public Boolean getCompleted() {
        return completed;
    }

    public void setCompleted(Boolean completed) {
        this.completed = completed;
    }

    public String getScores() {
        return scores;
    }

    public void setScores(String scores) {
        this.scores = scores;
    }

    public List<Bookmaker> getBookmakers() {
        return bookmakers;
    }

    public void setBookmakers(List<Bookmaker> bookmakers) {
        this.bookmakers = bookmakers;
    }

    public String getProgCorreto() {
        return progCorreto;
    }

    public void setProgCorreto(String progCorreto) {
        this.progCorreto = progCorreto;
    }

    @Override
    public String toString() {
        return "Jogo{" +
                "id='" + id + '\'' +
                ", homeTeam='" + homeTeam + '\'' +
                ", awayTeam='" + awayTeam + '\'' +
                ", commenceTime='" + commenceTime + '\'' +
                ", completed=" + completed +
                ", scores='" + scores + '\'' +
                ", bookmakers=" + bookmakers +
                '}';
    }
}