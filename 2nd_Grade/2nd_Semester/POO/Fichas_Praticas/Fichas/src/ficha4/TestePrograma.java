package ficha4;

import java.time.LocalDate;
import java.util.ArrayList;

public class TestePrograma {
    public static void main(String[] args){
        EncEficiente pak = new EncEficiente("Diogo",
                                          129166172,
                       "Joy's & Happiness's Avenue",
                                                 17,
                                    LocalDate.now(),
                   new ArrayList<>());

        System.out.println("\nPackage successfully created:\n"+ pak);

        LinhaEncomenda lineOne = new LinhaEncomenda("91346","Fragile Product",100,5,0.2,0.10);
        pak.adicionaLinha(lineOne);
        System.out.println("\nPackage line successfully inserted:\n"+ lineOne);

        LinhaEncomenda lineTwo = new LinhaEncomenda("16985","Oversea Product",500,2,1,0.25);
        pak.adicionaLinha(lineTwo);
        System.out.println("\nPackage line successfully inserted:\n"+ lineTwo);

        double totalValue = pak.calculaValorTotal();
        System.out.println("\nPackage total value: "+ totalValue +"\n[Predicted Value: 2040]\n");

        double discountValue = pak.calculaValorDesconto();
        System.out.println("Total Discount Value: "+ discountValue +"\n[Predicted Value: 940]\n");

        int numberProducts = pak.numeroTotalProdutos();
        System.out.println("Total Number of Products: "+ numberProducts +"\n[Predicted Value: 7 units]\n");

        String answerOne = pak.existeProdutoEncomenda("16985") ? "Yes.":"No.";
        String answerTwo = pak.existeProdutoEncomenda("22222") ? "Yes.":"No.";
        System.out.printf("Is there a product with the number [16985] ? %s", answerOne);
        System.out.println("\n[Predicted Answer: Yes.]\n");
        System.out.printf("Is there a product with the number [22222] ? %s", answerTwo);
        System.out.println("\n[Predicted Answer: No.]\n");

        pak.removeProduto("91346");
        System.out.println("Product [91346] removed.");
    }
}
