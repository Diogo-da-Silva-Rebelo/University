import ply.lex as lex

tokens = ( 'INI', 'FIM', 'nome', 'real', 'int', 'sinal' )
t_sinal = r'[=+\-*/()]'

def t_INI(t):
    r'(?i:begin)|\{'
    return t
def t_FIM(t):
    r'\}|[eE][nN][dD]'
    return t

def t_nome (t):
    r'[a-zA-Z)[a-zA-Z0-9]*'
    return t

def t_real(t):
    r'[0-9]+\.[0-9]+'
    return t

def t_int(t):
    r'[0-9]+'
    return t

t_ignore =  "\n\t"

def t_error(t):
    # ignorar erro e continuar a análise
   t.lexer.skip(1)

lexer = lex.lex()