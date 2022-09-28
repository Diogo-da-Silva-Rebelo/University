## 1+2 ou 1-2
import ply.lex as lex

tokens = ['NUM','MAI','MEN','MUL']

t_NUM = r'\d+'
t_MAI = r'\+'
t_MEN = r'-'
t_MUL = r'\*'

t_ignore = " \t\n"

def t_error(t):
    print('Caráter ilegal: ', t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()