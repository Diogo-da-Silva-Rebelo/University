package ficha2;

import java.time.LocalDate;
import java.util.Arrays;
import java.util.concurrent.TimeUnit;
import java.time.temporal.ChronoUnit;

public class Ex3 {
    private LocalDate[] datas; //é uma representação de uma data, ou seja, uma instância de um objeto.
    private int numDatas;

    /* Algumas formas de inicialização de datas:
     * LocalDate d1 = java.time.LocalDate.now();
     * LocalDate d2 = LocalDate.of(2021,03,03);
     */

    /* Vamos ter de criar um construtor deste array. Assim, quando este método é chamada com um tamanho N,
     * cria-se um array de datas com dimensão N e inicializa-se o número de datas a 0.
     */
    public Ex3(int N) {
        this.datas = new LocalDate[N];
        this.numDatas = 0;
    }

    //getter
    public LocalDate[] getDatas() {
        return datas;
    }

    public void insereDatas(LocalDate data) {
        if (this.numDatas < this.datas.length)
            this.datas[this.numDatas] = data;
        this.numDatas++;
    }

    /* O que ter em conta?
     -> Vamos ter de percorrer o array completo;
     -> Vamos ter de comparar a data recebida com cada uma das datas guardadas;
     -> Vamos ter de obter a diferença em dias entre as datas;
     -> Se a diferença entre as datas em questão for menor, então guardamos essa data, ignorando a outra;
     -> Arranjar método que faça esta comparação.
     */
    public LocalDate dataMaisProxima(LocalDate data) {
        long diffMenor = Math.abs(ChronoUnit.DAYS.between(data, this.datas[0]));
        LocalDate datamProx = this.datas[0];

        for (int i = 0; i < this.numDatas; i++) {
            LocalDate dataX = this.datas[i];
            long diffDias = Math.abs(ChronoUnit.DAYS.between(data, this.datas[i]));
            if (diffDias < diffMenor) {
                diffMenor = diffDias;
                datamProx = dataX;
            }
        }
        return datamProx;
    }

    @Override
    public String toString() {
        return "Ex3{" + "datas = " + Arrays.toString(datas) + ", numDatas =" + numDatas + '}';
    }
}
