class Packet():
   # int tipo = 0    # identifica o tipo da mensagem:  tipo 1 - flood | tipo 2 - activate | tipo 3 - overlay | tipo 0 - atualização de overlay | 4 - envio de vizinhos
    #int dados = 0   # dados do tipo custo a enviar: custo | 0 - activate
    #vizinhos = None # vizinhos de um determinado nodo
    
    def __init__(self,**args):
        if "bytes" not in args:
            self.packetID = args.get("packetID", None)
            self.type = args.get("type", None)
            self.ip_origin = args.get("ip_origin", None)
            self.ip_destination = args.get("ip_destino", None)
            self.latency = args.get("latencia", None)
            self.hops = args.get("nr_hops",None)
            self.port = args.get("port", None)
            self.payload = args.get("payload", None)
        else:
            self.bytesToPacket(args.get("bytes"))

    def getType(self):
        return self.type

    def getPacketID(self):
        return self.packetID

    def getIpDestino(self):
        return self.ip_destination

    def getIporigin(self):
        return self.ip_origin
    
    def getLatency(self):
        return self.latency
    
    def getHops(self):
        return self.hops

    def getPayload(self):
        return self.payload

    def bytesToPacket(self, bytes):
        msg = bytes.decode('utf8').split(';')
        self.packetID = msg[0]
        self.type = msg[1]
        self.ip_origin = msg[2]
        self.ip_destination = msg[3]
        self.latency = msg[4]
        self.hops = msg[5]
        self.port = msg[6]
        self.payload = msg[7]
        print("payload:")
        print(self.payload)

    def packetToBytes(self):
        msg = (";".join([str(self.packetID), str(self.type), self.ip_origin, self.ip_destination, self.latency, self.hops,str(self.port),
                        str(self.payload)])) + ";"
        return msg.encode('utf8')

    def toString(self):
        return ";".join([str(self.packetID), str(self.type), self.ip_origin, self.ip_destination, self.latency, self.hops, str(self.port),
                        str(self.payload)])

    def setIpDestino(self, ip):
        self.ip_destination = ip

    def setIpOrigin(self, ip):
        self.ip_destination = ip

    def printInfo(self):
        print(self.packetID)
        print(self.type)
        print(self.ip_origin)
        print(self.ip_destination)
        print(self.latency)
        print(self.hops)
        print(self.port)
        print(self.payload)