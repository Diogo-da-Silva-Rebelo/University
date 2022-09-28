import re

file = open("TextFiles/usernames.txt", "r")

for linha in file:
	m = re.search(r'(_|\.)(\d+)([A-Za-z]{3,})(_?|[A-Za-z]{1})$', linha)
	if m:
		print("VÁLIDO")
	else:
		print("INVÁLIDO")
file.close()