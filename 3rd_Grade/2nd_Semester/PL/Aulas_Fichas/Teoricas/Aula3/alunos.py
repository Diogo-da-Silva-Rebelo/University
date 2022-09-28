import re
import sys

# Ex feito na aula teórica que usa um ficheiro com a info dos alunos
# O objetivo é ler o ficheiro csv e agrupar os alunos de acordo com a regex definida, num dicionário.
# Cada aluno é um dicionário

aluno = r'(?:\"(?P<id>.+)\",)(?:\"(?P<nome>.+)\",)(?:\"(?P<curso>.+)\",)(?:(\d+),)(?:(\d+),)(?:(\d+),)(\d+)'
paluno = re.compile(aluno)

filer = open("alunos(1).csv", "r")
filew = open("alunosDict.txt", "a")

for linha in filer:
    maluno = paluno.search(linha)
    if maluno:
        dic = maluno.groupdict()
        filew.write(str(dic))
        filew.write("\n")
        print(dic)
filer.close()

# input: "a93344","luis","lcc",18,19,20,21  -> ele vai capturar.
# output: {'id': 'a93', 'nome': 'luis', 'curso': 'lcc', '18','19','20','21'}