## 1+2 
import ply.lex as lex

tokens = ['NUM', 'OP']

t_NUM = r'\d+'
t_OP = r'\+|-'

t_ignore = " \t\n"

def t_error(t):
    print('Caráter ilegal: ', t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()

