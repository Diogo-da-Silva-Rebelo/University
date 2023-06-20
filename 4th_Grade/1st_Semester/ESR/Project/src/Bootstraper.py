import socket, sys, os, _thread
from _thread import start_new_thread

nodes = {}

# no cenario2.txt mudei a terceira linha de 10.0.2.1 para 127.0.0.1

with open("../src/neighbours/cenario2.txt") as f:
    data = f.readlines()
    
    for line in data:
        parts = line.split('|')
        node = parts[0].strip()
        ips = [ip.strip() for ip in parts[1].split()]
        nodes[node] = ips
    print(nodes)

def multi_threaded_client(connection, address):
    try:
        msg = str.encode('\n'.join(nodes[address[0]]))
        connection.sendall(msg)
    except socket.error as e:
        print(str(e))

    connection.close()

host = sys.argv[1]
port = sys.argv[2]

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as ServerSideSocket:
    ServerSideSocket.bind((host,int(port)))

    ServerSideSocket.listen(1)

    while True:
        Client, address = ServerSideSocket.accept()
        print('Connected to: ' + address[0] + ':' + str(address[1]))
        start_new_thread(multi_threaded_client, (Client, address))
        
    ServerSideSocket.close()
    