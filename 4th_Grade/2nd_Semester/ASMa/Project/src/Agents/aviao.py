from spade import agent

#from Behaviours.intencaoAviao_Behav import IntencaoAviao_Behav
from Behaviours.registarAviao_Behav import RegistarAviao_Behav

from Behaviours.recebeConfirmacao_Behav import RecebeConfirmacao_Behav
from Classes.informaviao import InformAviao


class AviaoAgent(agent.Agent):

    companhia = None
    tipo = None
    id_aviao = None
    origem = None
    destino = None
    intencao = None

    async def setup(self):
        print("Aviao started")
        a= RegistarAviao_Behav()
        b= RecebeConfirmacao_Behav()

        self.add_behaviour(a)
        
        #c= RecebeConfirmacao_Behav()
        self.add_behaviour(b)
        #self.add_behaviour(c)