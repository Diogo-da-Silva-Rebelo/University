# Named groups
# Named Group é um grupo de captura com um nome.
# É da forma '?P<nome>...' onde ... é a expressão regular que dá forma a essa grupo.
# P.ex: Tendo (?P<pal>\b\w+\b), formamos o grupo 'pal' que captura de acordo com a expressão que se segue: \b\w+\b
# Neste caso, o exemplo acima captura todas as palavras.

import re
import sys

palavra = r'(?P<pal>\b\w+\b)'

for linha in sys.stdin:
    m = re.search(palavra, linha)
    if m:
        dic = m.groupdict()
        print(dic)
        # print(m.group(1))
        # print(m.group('pal'))
    else:
        print("No match...")

# input: ola
# output: ola

# COM DIC:
# input : ola
# output : {'pal' : 'ola'}
# se existissem mais palavras: {'pal': 'ola'; 'adeus'}