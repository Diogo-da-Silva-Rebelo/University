import re
import sys

# calcula a distribuição de uma palavra numa frase
def calcDistrib (texto):
    distrib = {}
    for c in texto:
        if c in distrib.keys:
            distrib[c] = distrib[c] + 1
        else:
            distrib[c] = 1
        return distrib
    print(calcDistrib("Hoje está a chover e nós estamos a assistir a uma aula"))

# x[0] é a chave e x[1] é o valor na espressão lambda
# ordena o dicionário por valor, primeiro converte para lista,
# depois faz a ordenação e volta a converter para dicionário
def novaDistrib ():
    d1 = calcDistrib("Hoje está frio")
    valores = list(d1.items())
    valores.sort(reverse=True,key=lambda x:x[1])
    novoDic = dict(valores)
    print(novoDic)