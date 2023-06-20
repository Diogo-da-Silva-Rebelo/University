from spade import agent
import asyncio 
import queue

from Behaviours.recebePedidosTorre_Behav import RecebePedidoTorre_Behav
from Behaviours.verificaFilaEspera_Behav import VerificaFilaEspera_Behav

class TorreControloAgent(agent.Agent):
    lista_avioes = []
    lista_esperateste = []

    async def setup(self):
        #self.fila_espera = asyncio.Queue(maxsize=5)
        print("Torre de Controlo Agent Started")
        a = RecebePedidoTorre_Behav()
        # executar o b de 3 em 3 segundos
        b = VerificaFilaEspera_Behav(8)

        self.add_behaviour(a)
        self.add_behaviour(b)