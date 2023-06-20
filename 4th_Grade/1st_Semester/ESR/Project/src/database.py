import threading
import time


class database:
    vizinhos: list
    nodes: dict
    lock: threading.Lock

    def __init__(self):
        self.vizinhos = list()
        self.nodes = dict()
        self.lock = threading.Lock()

    def acrescenta(self, add):
        self.lock.acquire()
        self.vizinhos.append(add)
        self.lock.release()

    def remove(self, add):
        self.lock.acquire()
        self.vizinhos.remove(add)
        self.lock.release()

    def get_vizinhos(self):
        self.lock.acquire()
        return self.vizinhos
        self.lock.release()

    def get_nodes(self):
        self.lock.acquire()

        # Loop through the IP addresses in the list of IP addresses
        for ip in self.vizinhos:
            # Add the IP address as a key to the new dictionary, with a
            # value of a list of 0s, 0s, and two strings
            self.nodes[ip] = [0, 0, None, None]
        
        return self.nodes
        self.lock.release()

    def show(self):
        self.lock.acquire()
        print(f"Os vizinhos são: \n")
        for v in self.vizinhos:
            print(str(v))
            print("\n")
            time.sleep(2)
        print("")
        self.lock.release()
        time.sleep(3)
