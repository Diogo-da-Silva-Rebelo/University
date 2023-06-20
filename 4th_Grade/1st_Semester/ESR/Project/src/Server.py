import socket
import threading
import time
import database
import sys
import traceback
import os
from _thread import start_new_thread
from Packet import Packet

# from RtpPacket import RtpPacket
# from streaming.VideoStream import VideoStream
# from ServerWorker import ServerWorker

VIZINHOS = '1'  # Enviado quando inicializado o nodo / server
VIZINHOS_ANN= '2'  # Enviado quando é recebido um Packet do tipo 1
DATA = '3'
REQUEST = '4'
STOP = '5'
FLOODING = 'F'


class Server:

    def __init__(self, port, alertport, params):

        # obter o ip do localhost
        # definir as variáveis "globais"
        self.host = self.ip() #socket.gethostbyname(socket.gethostname())
        self.port = port
        self.alertport = alertport

        # iniciar o socket (tcp)
        self.ServerSideSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.ServerSideSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        #self.ServerSideSocket.bind((self.host, self.port))

        # iniciar o socket
        self.RTPSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # lista de threads
        self.threads = []

        # IDENTIFICAÇÃO INICIAL DOS VIZINHOS
        # dict que guarda os vizinhos
        self.vizinhos = {}
        self.cen = params[0]

        self.dict_viz = self.read_vizinhos()
        print("\nLi estes vizinhos do ficheiro de configuração:\n")
        print(str(self.dict_viz))
        #print("\n")
        self.nodes = {}

        for v in self.dict_viz:
            if (v != self.host):
                self.nodes[v] = [0,0,None,None]

        """ Quando acaba de ler os vizinhos, cria este dict (não mete o seu ip):

        {
            ip1: [0,0,None,None], desligado, rota inativa, sTCP, sUDP
            ip2: [1,0,None,None], ligado, rota ativa, ...
            ...
        }
        """

        self.self_primeira_vez = 0

    
    def ip(self):
        i = 0
        from netifaces import interfaces, ifaddresses, AF_INET
        for ifaceName in interfaces():
            addresses = [i['addr'] for i in ifaddresses(ifaceName).setdefault(AF_INET, [{'addr':'No IP addr'}] )]
            if i == 1:
                return addresses[0]
            i+=1

    # fornece os vizinhos
    def read_vizinhos(self):
        # IDENTIFICAÇÃO INICIAL DOS VIZINHOS
        # dict que guarda os vizinhos

        filename = f"../src/neighbours/cenario{self.cen}.txt"

        nodes = {}
        with open(filename,'r') as f:
            data = f.readlines()
            for line in data:
                parts = line.split('|')
                node = parts[0].strip()
                
                ips = [ip.strip() for ip in parts[1].split(' ')]
                nodes[node] = ips
            # criar um novo dict com todos os ips tipo o que está abaixo
        f.close()
        #list_vizs = v[addrs]
        return nodes

            
    def serverListenerWorker(self, name):
        self.ServerSideSocket.bind((self.host, self.port))
        print(self.host,self.port)
        print(self.ServerSideSocket)
        self.ServerSideSocket.listen(5)

        while True:
            # cliente liga-se
            clientConn, addr = self.ServerSideSocket.accept()
            print('Got a connection from: ' + addr[0] + ': ' + str(addr[1]))


            # criar thread que se encarrega da conexão e de ouvir novos clientes
            x = threading.Thread(target=self.serverConnWorker, args=("serverConnWorker", addr, clientConn))
            self.threads.append(x)
            x.start()

    # lidar com multi-threading do cliente
    # trata de enviar a mensagem requerida
    def serverConnWorker(self, name, addr, conn):
        ipFrom = None

        while True:
            dados = conn.recv(1024)
            # Se os dados estiverem vazios
            if not dados:
                break
            # Se os dados tiverem alguma coisa
            data = dados.decode()
            # if ipFrom is None:
            #     ipFrom = addr[0]
            #     port = addr[1]
            #     tipo = data.split(';')[0]
            #     msg = data.split(';')[1]
            data = data.split(';')
            tipo = data[0]
            if (addr[0]=="127.0.0.1"):
                ipFrom = self.ip()
            else:
                ipFrom = addr[0]

            if  tipo == VIZINHOS:
                ipFrom = data[1]
                # verificar se já tem socket de TCP
                if ipFrom not in self.nodes: 
                    self.nodes[ipFrom] = [0,0,None,None]
                if self.nodes[ipFrom][2] is None:
                    self.nodes[ipFrom][2] = conn
                
                #try:
                    #endereco = self.nodes[ipFrom][2].getpeername()
                print("Socket is already connected to %s" % str(ipFrom))
                ''' except socket.error:
                    print("Socket is not connected")
                    self.nodes[ipFrom][2].connect((ipFrom, port))
                    print("New Client is connected.")'''

                self.nodes[ipFrom][0] = 1  # está ligado
                self.nodes[ipFrom][1] = 0  # rota inactiva

                nb = str(self.getVizinhosList(ipFrom))
                string = f"2;{nb}".encode()
                print(self.nodes[ipFrom])
                self.nodes[ipFrom][2].send(string)
                print("Response Sent")
            elif tipo == FLOODING:
                self.flood_handle(data,ipFrom)

            #conn.close()
        #print("Ligação caiu [" + name + "]\n")

        # desligar e rota inativa
        #self.nodes[ipFrom][0] = 0
        #self.nodes[ipFrom][1] = 0

        #if self.nodes[ipFrom][2] is not None:
        #    self.nodes[ipFrom][2].close()
        #    self.nodes[ipFrom][2] = None
        #print("Stoping sending to " + ipFrom)

    #def getVizinhosIps(self, ip):
    #    return self.vizinhos[ip]

    def getVizinhosList(self, ip):
        print (self.dict_viz)
        return self.dict_viz[ip]


    def start(self):
        # thread para ficar à escuta de novos clientes
        dataThread = threading.Thread(target=self.serverListenerWorker, args=("serverListenerWorker",))
        dataThread.start()

        # self.announce()

        print("[Server] Listening at " + self.host)

        # for i in self.threads:
        #  i.join()

        """
        # thread para enviar os pacotes de streaming
        streamingThread = threading.Thread(target=sendStreamingData, args=args=("sendData",))
        self.threads.append(datathread)
        streamingThread.start()

        # thread para input
        inputThread = threading.Thread(target=self.inputWorker,args=("inputThread",))
        self.threads.append(inputThread)
        inputThread.start()


        print("[Server] Listening at " + self.host)
        """

    # ADICIONAR AO LISTENER, EXECUTAR EM CASO DE DATA[0] SER 'F'
    def flood_handle(self, data, ip):
        print(f'Recebido pedido de flood de {ip}')
        print(data[1])
        self.flood_response(ip)

    def flood_response(self, ip):
        #if self.routing: 
            # F R IP N_SALTOS LATENCIA timestamp
        msg = f'F;R;{ip};{0};{0};{time.time()}'.encode()
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            print(ip)
            s.connect((ip, 5000))
            s.send(msg)
            print(f'Enviada resposta de flood para {ip}')
