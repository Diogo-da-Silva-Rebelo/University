import ply.lex as lex

tokens = ['NUM', 'SEP','LIMI', 'LIMF', 'START', 'END']

t_NUM = r'\d+'
t_LIMI = r'\['
t_LIMF = r'\]'
t_SEP = r','
t_START = r'(START)'
t_END = r'(END)'
t_ignore = " \t\n"

def t_error(t):
    print('Caráter ilegal: ', t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()