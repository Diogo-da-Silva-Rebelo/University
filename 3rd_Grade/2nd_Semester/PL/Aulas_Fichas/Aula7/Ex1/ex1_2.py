import ply.yacc as yacc
from tokenizer_list import tokens

# 1 END
# [], [1,2] [1,START,2,3,END], [START,END]

# def p_grammar(p):
#     """
#     Frase : LIMI Elementos LIMF
#     Elementos : Elementos SEP Elemento
#               | Elemento
#               | empty
#     Elemento : NUM
#               | START
#               | END
#     """
# Definir açoes sobre as produçoes de maneira a no final -> calculo da expressao



def p_Frase(p):
    "Frase : LIMI Elementos LIMF"

def p_Elementos(p):
    "Elementos : Elementos SEP Elemento"

def p_Elementos_simples(p):
    "Elementos : Elemento"

def p_Elementos_vazio(p):
    "Elementos : empty"

def p_Elemento(p):
    "Elemento : NUM"


def p_Elemento_limiteI(p):
    "Elemento : START"

def p_Elemento_limiteF(p):
    "Elemento : END"



def p_error(p):
    print ("Error:", p)
    parser.erro = True

def p_empty(p):
    'empty :'
    pass

parser = yacc.yacc()

import sys
for linha in sys.stdin:
    parser.output = 0
    parser.operacao = 1 # 1-soma, 2- subtração
    parser.erro = False # Controlar os erros
    parser.parse(linha) # Chamar o parse linha a linha
    if not parser.erro:
        print("Frase válida!")
        print(parser.output)
    else:
        print("Frase inválida... Corrija e tente novamente!")