import re

f = open("TextFiles/matriculas.txt", "r")

r = r'^[0-9]{2}(\.\.\.|-|\:)[0-9]{2}\1[0-9]{2}\1[0-9]{2}$'
rAlternativa = r'^\d{2}(\.\.\.|-|\:)\d{2}\1\d{2}\1\d{2}$'

for linha in f :
    m = re.search(r,linha)
    if m:
        print("Valido")
    else:
        print("Inválido")