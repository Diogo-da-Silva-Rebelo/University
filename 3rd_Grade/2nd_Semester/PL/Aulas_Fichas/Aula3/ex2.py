# Para definir um endereço de IP, temos de saber como definir o intervalo de inteiros 0-255:
# 1 - definir o intervalo 0-199: [01]?[0-9][0-9]?
# 2 - definir o intervalo 200-249: 2[0-4][0-9]
# 3 - definir o intervalo de 250-255: 25[0-5]
# 4 - a expressão final é a disjunção de todos os intervalos:
# adicionando a captura do ponto e exatamente três vezes esse conjunto 'A.'
# (([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\.){3}

import re

f = open("TextFiles/ip.txt", "r")
ipv4 = r'(([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\.){3}([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])'
ipv4Alternativa = r'^(([0-9]{2}|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]{2}|1[0-9]{2}|2[0-4][0-9]|25[0-5])'
ipv6 = r'([0-9a-f]{1,4}\:){7}[0-9a-f]{1,4}'

for linha in f:
    m = re.search(ipv4,linha)
    n = re.search(ipv6,linha)
    if m:
        print("Ipv4")
    elif n:
        print("Ipv6")
    else:
        print("Erro")

    



