# Ex1 - sub
import re
from unittest import skip
import ply.lex as lex
import sys

# 1234 -> numero
r = re.sub(r'[0-9]+',"numero",'''1234 asd
123456''')

#input: 1234
# output numero

r1 = re.sub(r'(asd) (dsf)',r'\2 injetar \1', "asdds")
#input: asddsf
#output: asd dsf

# Ex2
tokens = ["NUM","OPERADORES"]

t_NUM = '\d+'
t_OPERADORES = '[+|*|-]'

t_ignore ='\n\t '
def t_error(t):
    print("Erro")
    print(t)
    skip(1)

lexer = lex.lex()

for line in sys.stdin:
    lexer.input(line)
    for tok in lexer:
        print(tok)