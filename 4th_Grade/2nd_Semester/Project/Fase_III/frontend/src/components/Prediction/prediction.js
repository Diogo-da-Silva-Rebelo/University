import React from 'react';
import css from './prediction.module.css';

function Prediction() {
    return (
        <div className={css.title}>
            <h1>Previsão e Modelo</h1>

            <div className={css.plano}>
                <h2>Plano de ação</h2>

                <h3>
                    Preparar os dados:
                </h3>

                <p>
                    Recolha de dados históricos sobre a qualidade do ar de várias coordenadas em Braga.
                </p>

                <h3>Pré-processamento de dados:</h3>

                <p>
                    Limpar os dados, os outliers e assegurar o formato consistente. Dividir o conjunto de dados em conjuntos de treino e de teste.
                </p>

                <h3> Escolha da abordagem:</h3>
                <p>
                    Optar por métodos de interpolação ou treinar um modelo como por exemplo, completar.
                </p>

                <h3>Aplicar a abordagem escolhida:</h3>

                <p>
                    Interpolação: Aplicar a técnica de interpolação escolhida para estimar os valores da qualidade do ar
                    nas coordenadas pretendidas. Ajustar os parâmetros com base nas características do seu conjunto de
                    dados.
                </p>

                <p>
                    Aprendizagem automática: Selecionar um algoritmo adequado e
                    treinar o modelo utilizando os dados disponíveis. Avaliar o desempenho do modelo no conjunto de testes
                    para garantir sua precisão.
                </p>

                <h3>Prever a qualidade do ar:</h3>

                <p>
                    Depois de aplicada a interpolação ou treinar um modelo de aprendizagem
                    automática, utilizá-lo para prever os valores da qualidade do ar nas restantes coordenadas em
                    Braga.
                </p>
            </div>

            <div className={css.plano}>
                <h2>Modelo</h2>

                <h3>Interpolação</h3>

                <p>
                    A interpolação é um método de estimativa de valores desconhecidos dentro de um intervalo de dados

                    conhecidos.
                </p>

            </div>
        </div>
    );
}

export default Prediction;
