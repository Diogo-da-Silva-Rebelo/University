package ficha2;

import org.jetbrains.annotations.NotNull;
import java.util.*;

public class Ex5 {

    private String string;

    public void readString() {
        Scanner read = new Scanner(System.in);
        this.string = read.nextLine();

        System.out.println("\nThe inserted string was: " + "{ " + this.string + " }\n");
    }

    public String[] stoArrayStrings() {
        String[] arrayStrings;
        arrayStrings = this.string.split(" ");
        return arrayStrings;
    }

    public String[] noRepetitions(String[] arrayStrings) {
        arrayStrings = Arrays.stream(arrayStrings).distinct().toArray(String[]::new);
        //arrayStrings = new HashSet<>(Arrays.asList(arrayStrings)).toArray(new String[0]);
        return arrayStrings;
    }

    public String greaterString(String[] arrayStrings) {
        noRepetitions(arrayStrings);
        int maxlength = 0;
        String longestString = null;
        for (String s : arrayStrings) {
            if (s.length() > maxlength) {
                maxlength = s.length();
                longestString = s;
            }
        }
        return longestString;
    }

    public ArrayList<String> dupStrings(String[] array) {
        ArrayList<String> duplicate = new ArrayList<>();
        int dup = 0;

        for (int i = 0; i < array.length; i++) {
            for (int j = i + 1; j < array.length; j++) {
                if (array[i].equals(array[j])) {
                    duplicate.add(array[j]);
                    dup++;
                }

            }
        }
        System.out.println("Total number of repetitions: " + dup);
        return duplicate;
    }

    public int numberRep(String @NotNull [] array, String lookup) {
        int numberOfRep = 0;

        for (String s : array) {
            if (s.equals(lookup))
                numberOfRep++;
        }
            return numberOfRep;
    }
}