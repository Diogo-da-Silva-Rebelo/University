package ficha3;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class TestePrograma {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        char c1 = 'S';

        while (c1 != 'N') {
            System.out.println("Introduza o nº da pergunta: ");
            int pergunta = input.nextInt();

            // Como vamos ler sempre arrays, porque não criar um método que faça isso na classe Ficha2?
            switch (pergunta) {
                //A pergunta 0 é a pergunta relativa ao exemplo da implementação da Stack.
                case 0:
                    Stack stk = new Stack();
                    System.out.println("Vazia? "+ stk.empty());

                    for (int i = 0; i<10; i++)
                        stk.push("String ".concat(Integer.toString(i)));

                    System.out.println("Vazia? "+stk.empty());
                    System.out.println("Tamanho stack "+ stk.length());
                    System.out.println("Top "+ stk.top());
                    System.out.println("Stack "+ stk);

                    Stack stk2 = stk.clone();
                    System.out.println("Stk == stk2 ? "+ stk.equals(stk2));
                    for (int i=0; i<5; i++) stk2.pop();

                    System.out.println("Stk == stk2 ? "+ stk.equals(stk2));
                    System.out.println("Tamanho stack1 "+ stk.length());
                    break;
                case 1:
                    Ex1 c = new Ex1();
                    c.setRaio(1);
                    double p = c.calculaPerimetro();
                    System.out.println("Perímetro: " + p);
                    System.out.println(c);
                    c.alteraCentro(1, 1);
                    System.out.println(c);
                    double a = c.calculaArea();
                    System.out.println("Área: " + a);

                    Ex1 c2 = c.clone();
                    //Ex: //System.out.println(" c == c  ? " + c.equals(c));
                    System.out.println(" c == c2 ? " + c.equals(c2));
                    c2.setRaio(5);
                    System.out.println(" c == c2 ? " + c.equals(c2));
                    c.setRaio(5);
                    System.out.println(" c == c2 ? " + c.equals(c2));
                    break;
                case 2:
                    Ex2 phone = new Ex2("Apple","3Ot5", 10, 30, 45, 1024, new ArrayList<>(), 2048, 4960, 2000, 18, 20, new ArrayList<>());
                    System.out.println("New phone inserted: \n" + phone);

                    int newAppBytes = 1000;
                    System.out.println("Is there storage for an app with " + newAppBytes + "bytes? " + phone.isThereStorage(newAppBytes));

                    phone.installApp("Instagram",30);
                    phone.installApp("Pinterest",20);
                    phone.installApp("Lightroom",10);
                    phone.removeApp("Pinterest",20);

                    double avgSize = phone.avgAppSize();
                    int totalAppStorage = phone.getPhotoAndAppStorage();
                    int usedStorage = phone.getUsedStorage();
                    int freeSpace = totalAppStorage - usedStorage;
                    System.out.println("You still have " + freeSpace + " free bytes.");
                    System.out.println("Average App Size is " + avgSize);

                    phone.receiveMessage("Hello there mate! How's everything going ? ");
                    phone.receiveMessage("Hope you're okay ");
                    phone.receiveMessage("I love you. ");
                    phone.receiveMessage("XOXO, mum ");

                    System.out.println("User decided to check messages!" + phone.getMessages());
                    System.out.println("Biggest message is: " + phone.biggestMessage());
                    break;
                case 3:
                    Ex3 yt = new Ex3("Skincare Routine", "0101010001110110", LocalDate.of(2021,2,12), 1080, 3600, new ArrayList<>(),300,10);
                    System.out.println("New video called " + yt.getVideoName() + " created with success!\n");
                    yt.thumbsUp();
                    yt.insertComment("OMG! SOOO COOL");
                    yt.insertComment("dope!");
                    yt.insertComment("I need to get that brush!");
                    System.out.println("Video was uploaded " + yt.howManyDaysAfter() + " days ago.\n");
                    System.out.println("Comment List is: \n" + yt.getComments() + "\n");
                    System.out.println("Final Video Characteristics:\n" + yt);
                    yt.process();
                    //don't forget to see new file created!
                    break;
                case 4:
                    //finish
                    break;
                case 9:
                    Ponto a2 = new Ponto(0,0);
                    Ponto b2 = new Ponto(0,2);
                    Ponto c3 = new Ponto(5,0);
                    Triangulo triangulo1 = new Triangulo(a2,b2,c3);
                    a2.setX(-5);
                    System.out.println("Triângulo definido pelos pontos (0,0), (0,2) e (5,0).");
                    System.out.println(triangulo1 + "\n");
                    System.out.println("Área do triângulo = " + triangulo1.calculaAreaTriangulo());
                    System.out.println("Perímetro do triângulo = " + triangulo1.calculaPerimetroTriangulo());
                    System.out.println("Altura do triângulo = " + triangulo1.calculaAltura());

                    Triangulo triangulo2 = triangulo1.clone();
                    if (!triangulo1.equals(triangulo2)) System.out.println("Something is wrong with the equals or the clone functions.");

                default:
                    System.out.println("Input inválido.");
            }
            System.out.println("Deseja fazer outra pergunta? [S/N] ");
            Scanner careter = new Scanner(System.in);
            c1 = careter.next().charAt(0);
        }
    }
}
