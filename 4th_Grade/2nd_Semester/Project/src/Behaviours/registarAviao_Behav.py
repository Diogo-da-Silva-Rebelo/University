import random

from spade.behaviour import OneShotBehaviour
from spade.message import Message

from Classes.informaviao import InformAviao
import jsonpickle 

class RegistarAviao_Behav(OneShotBehaviour):
    async def run(self):
        companhias = ["Delta", "United", "American Airlines", "Lufthansa", "Emirates"]
    
        tipos = ["comercial", "carga"]
        
        companhia = random.choice(companhias)
        tipo = random.choice(tipos)
        intencao = random.choice(["aterrar", "descolar"])
        if intencao == "aterrar":
            origens = ["Londres", "Braga", "Paris", "Dubai", "São Paulo"]
            #destinos = ["Madrid", "Los Angeles", "Roma", "Bangkok", "Braga"]
            origem = random.choice(origens)
            #destino = random.choice(destinos)
            destino = "Braga"
            atrasado = '0'
        else: 
            destino = random.choice(["Londres", "Paris", "Dubai", "São Paulo"])
            origem = "Braga"
            atrasado = '0'
 
        self.agent.aviaocorrente = InformAviao(str(self.agent.jid), companhia, origem, destino,tipo, intencao,atrasado)
        msg = Message(to=self.agent.get("torre"))
        msg.body = jsonpickle.encode(self.agent.aviaocorrente)
        msg.set_metadata("performative", "request")
        await self.send(msg)
        
        print("Aviao {} registado".format(self.agent.aviaocorrente.id_aviao))
