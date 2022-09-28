import ply.yacc as yacc
from precedence_lex import tokens

# def p_grammar(p):
#     """
#     Frase       : Elementos
    # Elementos   : Elementos MAI Elementos
    #             | Elementos MEN Elementos
    #             | Elementos MUL Elementos
    #             | Expressao
#     Expressao   : NUM
#     """

# 1+2*3

precedence =(
    ('left','MAI','MEN'),
    ('left','MUL'),
)
def p_frase(p):
    "Frase       : Elementos"

def p_elementos_mais(p):
    "Elementos   : Elementos MAI Elementos"
    print("mais")

def p_elementos_menos(p):
    "Elementos   : Elementos MEN Elementos"
    print("menos")

def p_elementos_vezes(p):
    "Elementos   : Elementos MUL Elementos"
    print("vezes")

def p_elementos_expressao(p):
    "Elementos  : Expressao"
    p[0] = p[1]

def p_expressao(p):
    "Expressao  : NUM"
    p[0] = p[1]

def p_error(p):
    print('Erro sintático: ', p)
    parser.success = False

# Build the parser
parser = yacc.yacc()

# Read line from input and parse it
import sys
for linha in sys.stdin:
    parser.success = True
    parser.total = 0
    parser.parse(linha)
    if parser.success:
        print("Frase válida!")
    else:
        print("Frase inválida... Corrija e tente novamente!")