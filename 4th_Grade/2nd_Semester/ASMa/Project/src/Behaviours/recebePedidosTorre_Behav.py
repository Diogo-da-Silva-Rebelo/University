from spade.behaviour import CyclicBehaviour
from spade.message import Message

from Classes.informaviao import InformAviao
import jsonpickle

XMPP_SERVER = 'purp'

class RecebePedidoTorre_Behav(CyclicBehaviour):
        #def __init__(self,fila_espera):
         #   super().__init__()
           # self.fila_espera = fila_espera
        
        async def run(self):
            msg = await self.receive(timeout=10) # wait for a message for 10 seconds
            if msg:
                print(f"Mensagem de {msg.sender} para a torre recebida com sucesso")

                aviao_reg = jsonpickle.decode(msg.body)
                performative = msg.get_metadata('performative')
                print("--------------------------------\n")
                if performative == 'request':
                    print(f"Perfomativa request de {msg.sender} na torre de controlo")
                    
                   # print("Agent {}:".format(str(self.agent.jid)) + " Pedido de Aterrar {}".format(msg.body))
                    self.agent.lista_avioes.append(aviao_reg)
                    intencao = aviao_reg.get_intencao()
                    print("--------------------------------"+ intencao)
                    if intencao == "aterrar":
                        print(f"{msg.sender} enviou pedido de aterrar")
                        #msg_body = msg.body.split('-')
                        #id_aviao, tipo_aviao = msg_body[0], msg_body[1]
                        msggare = Message(to=f"gestorgares@{XMPP_SERVER}")
                        msggare.set_metadata('performative', 'request')
                        msggare.body = jsonpickle.encode(aviao_reg)
                        #msggare.body = id_aviao + '-' + tipo_aviao
                        await self.send(msggare)

                       

                    elif intencao == 'descolar':
                        aviao_reg = jsonpickle.decode(msg.body)
                        self.agent.lista_avioes.append(aviao_reg)
                        print(f"{msg.sender} enviou pedido de descolar")


                        #msg_body = msg.body.split('-')
                        #id_aviao, tipo_aviao = msg_body[0], msg_body[1]
                        msggare2 = Message(to=f"gestorgares@{XMPP_SERVER}")
                        msggare2.set_metadata('performative', 'request')
                        #msggare2.body = id_aviao + '-' + tipo_aviao
                        msggare2.body = jsonpickle.encode(aviao_reg)
                        print("Agent {}:".format(str(self.agent.jid)) + " Enviou para o gestor de gares Pedido de Descolar do aviao {}".format(msg.sender))
                        await self.send(msggare2)
                      

                elif performative == 'confirm':
                    print("Agent {}:".format(str(self.agent.jid)) + " enviou para o confirmacao na torre que pode executar {}".format(aviao_reg.get_id_aviao()))
                    
                    
                    msginfo = Message(to=f"infovoos@{XMPP_SERVER}")
                    msginfo.set_metadata('performative', 'inform')
                    msginfo.body = jsonpickle.encode(aviao_reg)
                                #msginfo.body = id_aviao + '-' + tipo_aviao + '-' + 'aterrar'
                    await self.send(msginfo)

                    #envia mensagem gestor de gares para libertar pista ou gare
                    msggare = Message(to=f"gestorgares@{XMPP_SERVER}")
                    msggare.set_metadata('performative', 'release')
                    msggare.body = jsonpickle.encode(aviao_reg)
                    await self.send(msggare)

                    print("MENSAGEM PARA ATERRAR AVIAO\n\n\n")
                    # envia mensagem para o aviao a dizer que pode aterrar/matar
                    id = aviao_reg.get_id_aviao()
                    print(id)
                    msgaviao = Message(to=id)
                    msgaviao.body = jsonpickle.encode(aviao_reg)
                    msgaviao.set_metadata('performative', 'confirm')
                    await self.send(msgaviao)

                elif performative == 'refuse':
                    # geta da fila de espera

                    espera = self.agent.get('lista_esperateste')
                    if espera is not None and len(espera) > 5:
                    #if self.fila_espera.full():
                        print("Agent {}:".format(str(self.agent.jid)) + " enviou para o aviao a aterrar noutro aeroporto {}".format(aviao_reg.get_id_aviao()))
                        id = aviao_reg.get_id_aviao()
                        aviao_reg.set_atrasado('2')
                        msgaviao = Message(to=id)
                        msgaviao.set_metadata('performative', 'refuse')
                        msgaviao.body = jsonpickle.encode(aviao_reg)
                        await self.send(msgaviao)
                    else:
                        print("AVIAOOOO ATRASADO -<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
                        espera = self.agent.get('lista_esperateste')
                        if espera is None:
                            espera = []
                        espera.append(aviao_reg)
                        self.agent.set('lista_esperateste', espera)
                        # print fila de espera com id de avioes e tipo
                        for elem in espera:
                            print(elem.get_id_aviao())
                            print("\n")
                        aviao_reg.set_atrasado('1')
                        msginfo = Message(to=f"infovoos@{XMPP_SERVER}")
                        msginfo.set_metadata('performative', 'inform')
                        msginfo.body = jsonpickle.encode(aviao_reg)
                        await self.send(msginfo)
                else:
                        print("erro ao ler perfomativa na torre {}".format(msg.body) + performative)
            else:
                print("Torre Did not received any message after 10 seconds")
