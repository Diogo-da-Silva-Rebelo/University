package ficha2;

import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

public class Ex7 {
    private int[] numbers = new int[5];
    private int[] stars = new int[2];

    public int[] userNumberSort(int[] numbers){
        Arrays.sort(numbers);
        return numbers;
    }
    public int[] userStarSort(int[] stars){
        Arrays.sort(stars);
        return stars;
    }

    public void keySort(){
        Arrays.sort(this.numbers);
        Arrays.sort(this.stars);
    }

    //there's repetition
    public void generateKey() {
        int[] randNumber = new int[5];
        int[] randStar = new int[2];

        for (int i = 0; i < 5; i++)
            randNumber[i] = ThreadLocalRandom.current().nextInt(1, 50);
        System.arraycopy(randNumber, 0, this.numbers, 0, 5);
        for (int j = 0; j < 2; j++)
            randStar[j] = ThreadLocalRandom.current().nextInt(1, 9);
        System.arraycopy(randStar, 0, this.stars, 0, 2);
    }

    //theres no repetition
    public void generateNKey2() {
        ArrayList<Integer> list = new ArrayList<>(50);
        for (int i = 1; i <= 50; i++) {
            list.add(i);  // list contains: [1,2,3,4,5,6,7,8,...,50]
        }
        Collections.shuffle(list); // list now contains: [9, 3, 1, 5, 8, 7, 2, 6, 4,...]

        int[] numbersAllArray = new int[list.size()];

        // ArrayList to Array Conversion
        for (int i = 0; i < list.size(); i++)
            numbersAllArray[i] = list.get(i);

        int[] numbersArray = Arrays.copyOfRange(numbersAllArray, 0, 5);
        this.numbers = Arrays.copyOf(numbersArray, 5);
    }

    public void generateSKey2() {
        ArrayList<Integer> list = new ArrayList<>(9);
        for (int i = 1; i <= 9; i++) {
            list.add(i);  // list contains: [1,2,3,4,5,6,7,8,...,50]
        }
        Collections.shuffle(list); // list now contains: [9, 3, 1, 5, 8, 7, 2, 6, 4,...]

        //conversion to array
        int[] starsAllArray = new int[list.size()];

        // ArrayList to Array Conversion
        for (int i = 0; i < list.size(); i++)
            starsAllArray[i] = list.get(i);

        int[] starsArray = Arrays.copyOfRange(starsAllArray, 0, 2);
        this.stars = Arrays.copyOf(starsArray, 2);
    }

    public int[] readNumbers() {
        Scanner in = new Scanner(System.in);
        System.out.println("Insert your numbers: ");

        int[] userN = new int[5];
        for (int i = 0; i < 5; i++)
            userN[i] = in.nextInt();
        return userN;
    }

    public int[] readStars() {
        Scanner p = new Scanner(System.in);
        System.out.println("Insert your stars: ");

        int[] userS = new int[2];
        for (int i = 0; i < 2; i++)
            userS[i] = p.nextInt();
        return userS;
    }

    public int[] compareNumbers (int[] numbers) {
        int[] check = new int[5];
        int k = 0;
        for (int index : numbers) {
            if (Arrays.binarySearch(this.numbers,index) >= 0) {
                check[k] = index;
                k++;
            }
        }
        return check;
    }

    public int[] compareStars (int[] stars){
        int[] check = new int[2];
        int k = 0;
        for (int index : stars) {
            if (Arrays.binarySearch(this.stars,index) >= 0) {
                check[k] = index;
                k++;
            }
        }
        return check;
    }

    public void checkAllKey(int[] numbers, int [] stars){
        if (Arrays.equals(numbers,this.numbers) && Arrays.equals(stars,this.stars)){
            int i = 0, j = 0;
            while (j < 50){
                StringBuffer  spaces = printSpaces(i);
                System.out.println(spaces + "Numbers: " + Arrays.toString(numbers) + " Stars:  " + Arrays.toString(stars));
                i+=4;
                j++;
            }
        }
        System.out.println(" Congrats! You've the key all correct!!!!\n");
    }

    public StringBuffer printSpaces (int n){
        char spaces = ' ';
        StringBuffer s = new StringBuffer();
        int i = 0;
        while(i <= n) {
            s.append(spaces);
            i++;
        }
        return s;
    }

    @Override
    public String toString() {
        return "Key {" +
                "numbers=" + Arrays.toString(numbers) +
                ", stars=" + Arrays.toString(stars) +
                " }\n";
    }
}
