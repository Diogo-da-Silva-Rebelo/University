package ficha2;
import java.util.Arrays;

public class Ex4 {
    private int[] arrayInteiros;

    public Ex4 (int[] array){
        this.arrayInteiros = new int[array.length];
        System.arraycopy(array,0,this.arrayInteiros,0, array.length);
    }

    public int[] ordena(){
        int[] ordenado = new int[this.arrayInteiros.length];
        System.arraycopy(arrayInteiros,0,ordenado,0,arrayInteiros.length);
        Arrays.sort(ordenado);
        return ordenado;
    }

    //Neste caso, não precisavamos de pôr o "this" porque não há confusão de tipos com o java.
    public int procuraB (int elemento){
        return Arrays.binarySearch(this.arrayInteiros,elemento);
    }
}
