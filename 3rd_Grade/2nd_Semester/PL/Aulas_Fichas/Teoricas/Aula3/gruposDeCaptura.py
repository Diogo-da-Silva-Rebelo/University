import re
import sys

# Ex1
inteiro = r'(\+|-)?(\d+)'
real = r'(\+|-)?(\d+)(?:\.(\d+))?'
pint = re.compile(inteiro)
preal = re.compile(real)

for linha in sys.stdin:
    m = pint.search(linha)
    print(m.groups())
    print(m.group())


# Groups() vs. Group
# Groups(): retorna qualquer captura da expressão regular que nós colocamos.
#     groups(), groups(1), groups(2) -> tuplos com o mesmo output -> dá sempre um tuplo com os matches encontrados.
# Group(x): retorna a substring que corresponde à nossa expressão regular, independentemente
# de a expressão que nós colocamos ter algum grupo de captura. Se tivermos group(1), o output é
# o primeiro grupo que fez match. Com group(2), o segundo e assim sucessivamente.
#     group(0) ou group() -> dá a string inteira correspondente à nossa regex.

# No exemplo acima:
# Com m.groups():
# input: ghdj -56     ->      output: ('-', '56')
# Com m.group():
# output: -56
# Com m.group(1,2,1): dá um tuplo com (1ºgrupo que fez match, 2ºgrupo que fez match, 1ºgrupo que fez match)
# input: -88        ->      output: ('-', 88, '-')

# Ex2
real = r'(\+|-)?(\d+)(?:\.\d+)?' # remove toda a parte decimal
real2 = r'(\+|-)?(\d+)(?:\.(\d+))?' # remove o ponto, mas captura a parte decimal numérica

# Ao usarmos '?:' estamos a dizer que o que se segue a isso não é para ser capturado.

# Ex3
# verifica a existência de palavra duplicada: 'dd dd', por exemplo
palavraDobrada = r'\b(\w+)\s+\1\b'


# Este '\1' é como se substituísse o primeiro grupo de captura '(\w+)'.

for linha in sys.stdin:
    m = re.search(palavraDobrada, linha)
    if m:
        print(m.groups())
        print(m.group())
    else:
        print("No match...")

# input: Hoje em dia         dia
# output: ('dia',)

# input: Hoje em dia é dia
# output: No Match
