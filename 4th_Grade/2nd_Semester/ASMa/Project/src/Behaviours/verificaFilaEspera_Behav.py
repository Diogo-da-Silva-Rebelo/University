from spade.behaviour import PeriodicBehaviour
from spade.message import Message
import jsonpickle
from Classes.informaviao import InformAviao

XMPP_SERVER = "purp"

# a torre tem este comportamento
class VerificaFilaEspera_Behav(PeriodicBehaviour):
    async def run(self):
        #verifica se a fila de espera tem elementos
        espera = self.agent.get('lista_esperateste')
        print("VERIFICA FILA ESPERA -<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
        if espera is None or len(espera) == 0:
             print("Fila de espera vazia")
             print("---------------")
    
        elif len(espera) > 0:
            print("Fila de espera nao vazia")
            print("Fila de espera:")
            for aviao in espera: print(aviao)
            print("PERIODICOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO")
            print(espera[0])


            #verifica se ha pistas livres ao enviar uma mensagem para o gestor de gares
            msggare = Message(to=f"gestorgares@{XMPP_SERVER}", sender=str(self.agent.jid))
            msggare.set_metadata('performative', 'request')
                #msg body tem o jsonpickle do aviao
                #print(self.agent.fila_espera._queue[0].get_id_aviao())
            msggare.body = jsonpickle.encode(espera[0])
            await self.send(msggare)

            #espera pela resposta do gestor de gares
            msg = await self.receive(timeout=7) # wait for a message for 7 seconds
            print("MENSAGEMMMMMMMMM" + str(msg))
            if msg:
                print(f"{msg.sender} respondeu: {msg.body}")
                if msg.sender == f"gestorgares@{XMPP_SERVER}":
                    print("Recebe mensagem do gestor de gares")
                    #se a resposta for positiva, remove o aviao da fila de espera e envia uma mensagem para o aviao
                        #perfomative == confirm
                    if msg.get_metadata('performative') == 'confirm':
                        print("verificaFILABEHAV confirm -------------------------------")
                        aviao_reg = jsonpickle.decode(msg.body)
                        #remove aviao da fila de espera
                        print(aviao_reg)
                        for aviao in espera:
                            #aviao = jsonpickle.decode(aviao_encoded)
                            if aviao.get_id_aviao() == aviao_reg.get_id_aviao():
                                espera.remove(aviao)
                                print("REMOVIDO DA FILA DE ESPERA")
                                break
                            
                        #self.agent.lista_esperateste.pop(0)
                        aviao_reg.set_atrasado('0')
                        print("ID AVIAO: " + aviao_reg.get_id_aviao())
                        msgaviao = Message(to=aviao_reg.get_id_aviao())
                        msgaviao.set_metadata('performative', 'confirm')
                        msgaviao.body = jsonpickle.encode(aviao_reg)
                        await self.send(msgaviao)
                        msginfo = Message(to=f"infovoos@{XMPP_SERVER}")
                        msginfo.set_metadata('performative', 'inform')
                        msginfo.body = jsonpickle.encode(aviao_reg)
                                #msginfo.body = id_aviao + '-' + tipo_aviao + '-' + 'aterrar'
                        await self.send(msginfo)
                    elif msg.get_metadata('performative') == 'refusefila':
                            #CONTINUA NA FILA DE ESPERA
                        print("CONTINUA NA FILA--------------------------")

                    else:
                        print("perfomativa nao reconhecida aqui"+msg.get_metadata('performative'))
                else:
                    print("Mensagem de outro agente: " + str(msg.sender))
            else:
                print("No message received after 10 seconds")
            

            



