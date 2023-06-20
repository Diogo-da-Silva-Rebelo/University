import time, socket, sys, threading, ast
from Packet import Packet

VIZINHOS = '1'  # Enviado quando inicializado o nodo / server
VIZINHOS_ANN = '2'  # Enviado quando é recebido um Packet do tipo 1
DATA = '3'
REQUEST = '4'
STOP = '5'
FLOODING = 'F'


class Node:

    routing :list
    encaminhamento :list

    def __init__(self, params):
        # obter ip do host
        self.host = self.ip() #socket.gethostbyname(socket.gethostname())

        # iniciar socket TCP
        AddressPortAlert = ("", 5000)
        self.alertSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.alertSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.alertSocket.bind(AddressPortAlert)
        self.alertSocket.listen()

        # lista de threads
        self.threads = []

        # lista vizinhos
        self.vizinhos = []
        # nodos
        self.nodes = {}
        
        self.routing = []
        self.encaminhamento = [] 
        

        self.cen = params[0]
        bootaddrs_string = params[1:]
        self.bootaddrs = str(bootaddrs_string).replace('[','').replace(']','').replace("\'",'').replace(",",'')
        #print(self.bootaddrs)
        self.listaddrs = self.bootaddrs.split(" ")
        
        self.self_primeira_vez = 1

    # Esta função trata todas as mensagens recebidas.
    def trataMensagem(self,mensagem):
        #2;['x.x.x.x', 'x.x.x.x.x']
        mensagem.split(";")
        #2 -> indice 0 
        #['x.x.x.x', 'x.x.x.x.x'] -> indice 1
        tipo = mensagem[0]
        if(tipo=="2"):
            mensagem[1].ip = str(self.bootaddrs_string).replace('[','').replace(']','').replace("\'",'').replace(",",'')
            #x.x.x.x x.x.x.x.x -> indice 1
            ips=mensagem[1].split(" ")
            #x.x.x.x -> indice 0 
            #x.x.x.x -> indice 1
            for ip in ips:
                self.vizinhos.append(ips[ip])
                
        #elif(tipo=="3")
        print(self.vizinhos)


    def trataVizinhos(self,lista):
        lista = lista.split(';')[1].replace('[','').replace(']','').replace("\'",'').replace(",",'')
        for i in lista.split(' '):
            self.vizinhos.append(i)
                
            
    
    def ip(self):
        i = 0
        from netifaces import interfaces, ifaddresses, AF_INET
        for ifaceName in interfaces():
            addresses = [i['addr'] for i in ifaddresses(ifaceName).setdefault(AF_INET, [{'addr':'No IP addr'}] )]
            if i == 1:
                return addresses[0]
            i+=1

    def initNodos(self,msg):
        list_viz = ast.literal_eval(msg)
        for v in list_viz:
            self.nodes[v] = [0,0,None,None]
        self.self_primeira_vez = 0


    # iniciando, o nodo diz que entrou na topologia
    def alertWorker(self, name):

        if self.self_primeira_vez == 1:
            print(self.listaddrs,"Lista de ips")
            with socket.socket(family=socket.AF_INET,type=socket.SOCK_STREAM) as s:
                s.connect((self.listaddrs[0], 5000))
                msg = f"1;"+self.ip()
                print(msg)
                s.send(msg.encode())
                
                # receive first data from server
                data = s.recv(1024)
                print("recebeu?")
                lista = data.decode()
                print("A minha lista de vizinhos é:\n")
                print(lista)
                self.trataVizinhos(lista)

        # espera por conexões no socket
        
        print("passei aqui")
        while True:   
            print(self.alertSocket)
            # aceita conexão
            conn, addr = self.alertSocket.accept()
            print('[alertWorker] Connected by', addr)

            # inciar thread para tratar dos pedidos
            thread = threading.Thread(target=self.alertReceiverWorker, args=("alertReceiverWorker", conn, addr))
            
            self.threads.append(thread)
            
            thread.start()
            

            # iniciar thread para tratar de cenas com o bootstrapper
            # inciar thread para tratar dos pedidos


    def alertReceiverWorker(self, name, conn, addr):
        ipFrom = None
        while data := conn.recv(1024):
            if data:
                data = data.decode()
                if ipFrom == None:
                    if (addr[0]=="127.0.0.1"):
                        ipFrom = self.ip()
                    else:
                        ipFrom = addr[0]
                    port = addr[1]

                data = data.split(';')
                
                tipo = data[0]
                msg = data[1]

                # O nodo dá alerta de que está na topologia

                """if tipo == VIZINHOS:
                    self.initNodos(msg)
                    if ipFrom in self.nodes:
                        self.nodes[ipFrom][0] = 1
                        if self.nodes[ipFrom][2] is None:
                            self.nodes[ipFrom][2] = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                        self.nodes[ipFrom][2].connect((ipFrom, 5000))

                        
                        else:
                            print("Não sou bootstrapper. \n")
                """
                # O nodo recebe um alerta do server, ficando ativo
                if tipo == VIZINHOS_ANN:
                    self.initNodos(msg)
                    # se o nodo de quem recebi está ligado
                    if self.nodes[ipFrom][0] == 1:
                        print("Server connected\n")

                        # se está ligado, mas não tem um TCP socket, atualizamos
                        if self.nodes[ipFrom][2] is None:
                            self.nodes[ipFrom][2] = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

                        # se está ligado e tem socket, vamos conectar
                        self.nodes[ipFrom][2].connect((ipFrom, 5000))
                        print("Connected to " + str(ipFrom) + "[" + name + "]\n")
                elif tipo == FLOODING:
                    self.flood_handle(data,ipFrom)
                else:
                    print("Aconteceu algum erro.")

    def getVizinhosIps(self, ip):
        return self.vizinhos[ip]

    def flooding_timer(self):
        print(f'ENTREI AQUI {self.vizinhos}')
        while len(self.vizinhos) == 0:
            time.sleep(0.5)
        print('PASSEI!')
        while True:
            self.flood_request()
            time.sleep(10)


    def flood_request(self):
        print("ENTREI AQUI REQUEST")
        
        for ip in self.vizinhos:
            if ip not in self.routing:
                with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                    try:
                        print("A enviar request de flood")
                        s.connect((ip, 5000))
                        s.send(f'F;{self.ip}'.encode())
                    except Exception:
                        continue

    def flood_response(self, ip):
        if len(self.routing) == 0: 
            # F R IP N_SALTOS LATENCIA timestamp
            msg = f'F;R;{self.ip};{self.routing[1]};{self.routing[2]};{time.time()}'.encode()
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                print('A responder')
                s.connect((ip, 5000))
                s.send(msg.encode())

    def flood_handle(self, data, ip):

        if data[1] == 'R': # F;R;<IP> ...
            print(f'A adicionar resposta à minha routing')
            latencia = float(data[-2]) + (time.time() - float(data[-1]))
            if len(self.routing) == 0 or latencia < self.routing[2]:
                self.routing = []
                self.routing.append(data[2])
                self.routing.append(data[3])
                self.routing.append(latencia)
        else: # F <IP>
            print(f'Alguém me pediu flood, vou responder? {len(self.routing) == 0}')
            self.flood_response(self.routing[0])


    def streaming(self):
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
                s.connect((self.ip, 6000))
                data = s.recv(20480)
                for ip in self.encaminhamento():
                    s.sendto(data,(ip,6000))



    def start(self):
        first_Thread = threading.Thread(target=self.alertWorker, args=("alertworker",))  # 5000
        self.threads.append(first_Thread)
        first_Thread.start()
        thread_Flood = threading.Thread(target=self.flooding_timer, daemon=True)
        self.threads.append(thread_Flood)
        thread_Flood.start()

        #self.announce()
