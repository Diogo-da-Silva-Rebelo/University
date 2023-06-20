PRESENT = '1' # Enviado quando inicializado o nodo / server
ANNOUNCEMENT = '2' # Enviado quando é recebido um Packet do tipo 1
DATA = '3'
REQUEST = '4'
STOP = '5'


HEADER = '\033[95m'
OKBLUE = '\033[94m'
OKCYAN = '\033[96m'
OKGREEN = '\033[92m'
WARNING = '\033[93m'
FAIL = '\033[91m'
ENDC = '\033[0m'
BOLD = '\033[1m'
UNDERLINE = '\033[4m'
INFO = '\33[93m'

def printDebug(text,who="",end="\n"):
    if who=="":
        print(f"{INFO}{text}{ENDC}",end=end)
    else:
        print(f"{INFO}[{who}]{text}{ENDC}",end=end)
    
def printSuccess(text,who="",end="\n"):
    if who=="":
        print(f"{OKGREEN}{text}{ENDC}",end=end)
    else:
        print(f"{OKGREEN}[{who}]{text}{ENDC}",end=end)
    
def printError(text,who="",end="\n"):
    if who=="":
        print(f"{FAIL}{text}{ENDC}",end=end)
    else:
        print(f"{FAIL}[{who}]{text}{ENDC}",end=end)