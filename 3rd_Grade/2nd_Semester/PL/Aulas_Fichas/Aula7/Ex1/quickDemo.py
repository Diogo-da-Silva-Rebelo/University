import ply.yacc as yacc
import sys
from listas_lex import tokens


# def p_grammar(p):
#     """
#     Frase : Elementos
#     Elementos : Elementos OP Elemento
#               | Elemento
#     Elemento : NUM
#     """
# Definir açoes sobre as produçoes de maneira a no final -> calculo da expressao


def p_Frase(p):
    "Frase : Elementos"


def p_Elementos(p):
    "Elementos : Elementos OP Elemento"
    print(p[1], p[2], p[3])
    # if(p[1]):
    #     # Pegar nos elementos abaixo e efetuar a op de acordo com o OP
    #     if(p[2]=="+"):
    #         parser.output += int(p[1])+int(p[3])
    #     else:
    #         parser.output += int(p[1])-int(p[3])
    # else:
    #     # Pegar nos elementos abaixo e efetuar a op de acordo com o OP
    #     if(p[2]=="+"):
    #         parser.output += int(p[3])
    #     else:
    #         parser.output -= int(p[3])


def p_Elementos_simples(p):
    "Elementos : Elemento"
    p[0] = p[1]


def p_Elemento(p):
    "Elemento : NUM"
    # print(p[1])
    # Verificar a flag 
    # somo ou subtraio ao output
    p[0] = p[1]


def p_error(p):
    print("Error:", p)
    parser.erro = True


parser = yacc.yacc()

for linha in sys.stdin:
    parser.output = 0
    parser.operacao = 1  # 1-soma, 2- subtração
    parser.erro = False  # Controlar os erros
    parser.parse(linha)  # Chamar o parse linha a linha
    if not parser.erro:
        print("Frase válida!")
        print(parser.output)
    else:
        print("Frase inválida... Corrija e tente novamente!")
