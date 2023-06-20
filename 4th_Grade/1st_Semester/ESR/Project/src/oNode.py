import sys
from Server import Server
from Node import Node
import socket
import database


def main():
    
    # ott.py -s <cenario>
    params = sys.argv[1:]
    isServer = False 
    
    if "-s" in params:
        isServer = True
        params.remove("-s")

        SERVER_PORT = 5000
        ALERTPORT = 6000
        
        server = Server(SERVER_PORT,ALERTPORT, params)
        server.start()
        
    # ott.py <cenario> <ser_ip>
    elif len(params) > 0:
        HOST = sys.argv[2]
        print(sys.argv[2])
        PORT = int(sys.argv[3])
        
        node = Node(params)
        node.start()
          
#    try:
#        addr = '127.0.0.1'
#        port = 25000
#    except:
#        print("[Usage: Cliente.py]\n")
#
#    root = Tk()
#	
#	# Create a new client
#    app = ClienteGUI(root, addr, port)
#    app.master.title("Cliente Exemplo")	
#    root.mainloop()
if __name__ == "__main__":
    main()
        
        
"""def main(args):
    db = database
    TCPServerSocket = socket.socket(socket.AF_INET,type=socket.SOCK_STREAM)
    ip = get
    
    #Se for o bootstraper
    if args[0] == ip:
        bootstraper(ip)
        
    elif(len(args)>0):
        for arg in args[1:]:
            database.acrescenta([arg])
            sendTCPMessage("New Node"+delim,arg)
            
    else:
        sendTCPMessage("Ask Neighbours"+delim+ip,args[0])
    
    threading.Thread(target=redirectRTP).start()
    
    while True:
        connectionSocket , addr = TCPServerSocket.accept()
        threading.Thread(target=receiveTCPMessage,args=(connectionSocket,addr)).start()
        
    except Exception as e:
        print("Error",e)
        TCPServerSocket.close()"""