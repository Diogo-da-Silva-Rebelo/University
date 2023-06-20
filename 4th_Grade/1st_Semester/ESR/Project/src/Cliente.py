import socket
import sys

#from tkinter import Tk
#from ClientGUI import ClienteGUI

def main():
    s: socket.socket
    mensagem: str
    endereco: str
    porta: int

    HOST = sys.argv[1]
    PORT = int(sys.argv[2])


    # passar ip do servidor
    #HOST = sys.argv[2]

    # s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # endereco = 'localhost'

    # print(sys.argv[0])
    # porta = int(sys.argv[1])

    # mensagem = "Adoro Redes :)"
    # s.connect
    # s.sendall(mensagem.encode('utf-8'), (endereco, porta))

    # msg, add = s.recvfrom(1024)

    # print(f"Recebi {msg.decode('utf-8')} do {add}")

    print("Os meus vizinhos são:")
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind(("",5001))
            s.connect((HOST, PORT))
            s.sendall("1;".encode())
            print("antes")
            data = s.recv(1024)
            print("depois")
            print(data.decode())
    except Exception as e : 
        print(e)

if __name__ == "__main__":
    main()

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