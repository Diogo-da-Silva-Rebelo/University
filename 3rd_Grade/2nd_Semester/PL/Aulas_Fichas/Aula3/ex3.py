import re
# [0-9]|[1-8][0-9] -> tem os nºs de 0 a 9 ou de 10 a 89 (que é como se fosse de 0 a 89. O 90 é posto como caso à parte)
# define-se o intervalo de 180 do mesmo modo.
f = open("TextFiles/latlon.txt", "r")

latlon = r'^\((\+|-)?((([0-9]|[1-8][0-9])(\.[0-9]+)?)|90(\.0+)?)\, (\+|-)?((([0-9]|[1-9][0-9]|1[0-7][0-9])(\.[0-9]+)?)|180(\.0+)?)\)$'


for linha in f:
    m = re.search(latlon,linha)
    if m:
        print("Válido")
    else: print("Inválido")
