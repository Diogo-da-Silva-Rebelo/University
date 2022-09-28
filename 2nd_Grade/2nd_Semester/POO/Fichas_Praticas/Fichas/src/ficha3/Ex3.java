package ficha3;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.List;

public class Ex3 {
    private String videoName;
    private String content;
    private LocalDate date;
    private int resolution;
    private int timeInSec;
    private List<String> comments;
    private int likes;
    private int dislikes;

    //Constructors
    //Empty
    public Ex3(){
        setVideoName("");
        setContent("");
        setDate(LocalDate.now());
        setResolution(0);
        setTimeInSec(0);
        setComments(new ArrayList<>());
        setLikes(0);
        setDislikes(0);
    }

    //Parametric
    public Ex3(String videoName, String content, LocalDate date, int resolution, int timeInSec, List<String> comments, int likes, int dislikes) {
        this.setVideoName(videoName);
        this.setContent(content);
        this.setDate(date);
        this.setResolution(resolution);
        this.setTimeInSec(timeInSec);
        this.setComments(comments);
        this.setLikes(likes);
        this.setDislikes(dislikes);
    }

    //Copy
    public Ex3 (Ex3 yt){
        this.videoName = yt.getVideoName();
        this.content = yt.getContent();
        this.date = yt.getDate();
        this.resolution = yt.getResolution();
        this.timeInSec = yt.getTimeInSec();
        this.comments = yt.getComments();
        this.likes = yt.getLikes();
        this.dislikes = yt.getDislikes();
    }

    //getter & setters
    public String getVideoName() {
        return this.videoName;
    }

    public void setVideoName(String videoName) {
        this.videoName = videoName;
    }

    public String getContent() {
        return this.content;
    }

    public void setContent(String content) {
        this.content = content;
        //this.content.addAll(content); -> se content fosse List<>.
    }

    public LocalDate getDate() {
        return this.date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public int getResolution() {
        return this.resolution;
    }

    public void setResolution(int resolution) {
        this.resolution = resolution;
    }

    public int getTimeInSec() {
        return this.timeInSec;
    }

    public void setTimeInSec(int timeInSec) {
        this.timeInSec = timeInSec;
    }

    public List<String> getComments() {
        return this.comments;
    }

    public void setComments(List<String> comments) {
        this.comments = new ArrayList<>(comments);
    }

    public int getLikes() {
        return this.likes;
    }

    public void setLikes(int likes) {
        this.likes = likes;
    }

    public int getDislikes() {
        return this.dislikes;
    }

    public void setDislikes(int dislikes) {
        this.dislikes = dislikes;
    }

    //methods
    public void insertComment(String comment){
        this.comments.add(comment);
    }

    public long howManyDaysAfter(){
        LocalDate now = LocalDate.now();
        LocalDate uploadDate = this.date;
       return ChronoUnit.DAYS.between(uploadDate, now);
    }

    public void thumbsUp(){
        this.likes++;
    }

    public void process(){
        //Temos uma lista de inteiros (0 ou 1), vamos:
        //1. Juntar todos este 0's e 1's
        //2. Colocá-los num ficheiro de texto
       creatNewFile();
       writeInFile();
    }

    public void creatNewFile(){
        try {
            File myObj = new File("/home/diogo/IdeaProjects/Programacao-Orientada-aos-Objetos/Fichas/src/ficha3/Render.txt");
            if (myObj.createNewFile()) {
                System.out.println("File created: " + "Render");
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public void writeInFile(){
            try {
                FileWriter myWriter = new FileWriter("/home/diogo/IdeaProjects/Programacao-Orientada-aos-Objetos/Fichas/src/ficha3/Render.txt");
                myWriter.write(getContent());
                myWriter.close();
                System.out.println("Successfully wrote to the file.");
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
    }

    @Override
    public String toString() {
        return "Ex3 {\n" +
                "videoName = " + videoName + '\n' +
                ", content = " + content + '\n' +
                ", date = " + date + '\n' +
                ", resolution = " + resolution + '\n' +
                ", timeInSec = " + timeInSec + '\n' +
                ", comments = " + comments + '\n' +
                ", likes = " + likes + '\n' +
                ", dislikes = " + dislikes + '\n' +
                "}\n";
    }
}

