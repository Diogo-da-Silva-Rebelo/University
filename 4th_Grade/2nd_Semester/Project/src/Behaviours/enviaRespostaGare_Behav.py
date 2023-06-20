from spade.behaviour import CyclicBehaviour
from spade.message import Message
import jsonpickle
from Classes.informaviao import InformAviao

XMPP_SERVER = 'purp'

class EnviaRespostaGare_Behav(CyclicBehaviour):

    async def run(self):
        msg = await self.receive(timeout=10)
        if msg:
            print("Mensagem para o gestor de gares recebida com sucesso de aviao para aterrar {}".format(msg.sender))

            performative = msg.get_metadata('performative')
            print("--------------------------------\n")

            if performative == 'request':

                aviao_reg = jsonpickle.decode(msg.body)

                if aviao_reg.get_intencao() == "aterrar":
                    print("INTENCAO ATERRAR GESTOR GARES")
                    print("Agent {}:".format(str(self.agent.jid)) + " Pedido de Disponibilidade de Gares e Pista {}".format(msg.sender))
                    #id_aviao, tipo_aviao = msg.body.split('-')
                    #aviao_reg = jsonpickle.decode(msg.body)
                    tipo = aviao_reg.get_tipo()
                    print(tipo+"-------------------")


                    lista_gares = self.agent.get("lista_gares")
                    lista_pistas = self.agent.get("lista_pistas")

                    gare_disponivel = False
                    for gare in lista_gares:
                        if gare['tipo'] == tipo and not gare['ocupacao']:
                            gare['ocupacao'] = True
                            gare_disponivel = True
                            self.agent.set("lista_gares", lista_gares)
                            break

                    pista_disponivel = False
                    for pista in lista_pistas:
                        if not pista['ocupacao']:
                            pista['ocupacao'] = True
                            pista_disponivel = True
                            self.agent.set("lista_pistas", lista_pistas)
                            break

                    msg_resposta = Message(to=f"torrecontrolo@{XMPP_SERVER}")
                    if gare_disponivel and pista_disponivel:
                        msg_resposta.set_metadata("performative", "confirm")
                    else:
                        msg_resposta.set_metadata("performative", "refuse")
                        if (not gare_disponivel):
                            print("gare indisponivel")
                        else:
                            print("pista indisponivel")
                    msg_resposta.body = jsonpickle.encode(aviao_reg)
                    await self.send(msg_resposta)

                if aviao_reg.get_intencao() == "descolar":
                    print("INTENCAO DESCOLAR GESTOR GARES")
                    #id_aviao, tipo_aviao = msg.body.split('-')
                    #aviao_reg = jsonpickle.decode(msg.body)
                    print("Mensagem para o gestor de gares recebida com sucesso de aviao a descolar {}".format(msg.sender))
                    print("Agent {}:".format(str(self.agent.jid)) + " Pedido de Disponibilidade de Pista {}".format(msg.sender))
                    lista_pistas = self.agent.get("lista_pistas")

                    disponivel = False
                    for pista in lista_pistas:
                        if not pista['ocupacao']:
                            pista['ocupacao'] = True
                            disponivel = True
                            self.agent.set("lista_pistas", lista_pistas)
                            break

                    msg_resposta = Message(to=f"torrecontrolo@{XMPP_SERVER}")
                    if disponivel:
                        msg_resposta.set_metadata("performative", "confirm")
                    else:
                        msg_resposta.set_metadata("performative", "refuse")
                   
                    msg_resposta.body = jsonpickle.encode(aviao_reg)
                    #msg_resposta.body =id_aviao + '-' + tipo_aviao
                    await self.send(msg_resposta)

 
            elif performative == 'release':
                print("Agent {}:".format(str(self.agent.jid)) + " Gare/Pista libertada {}".format(msg.sender))
                aviao_reg = jsonpickle.decode(msg.body)
                if aviao_reg.get_intencao() == "aterrar":
                    lista_gares = self.agent.get("lista_gares")
                    for gare in lista_gares:
                        if gare['tipo'] == aviao_reg.get_tipo():
                            gare['ocupacao'] = False
                            self.agent.set("lista_gares", lista_gares)
                            break
                    lista_pistas = self.agent.get("lista_pistas")
                    for pista in lista_pistas:
                        if pista['ocupacao']:
                            pista['ocupacao'] = False
                            self.agent.set("lista_pistas", lista_pistas)
                            break
            else:
                print("erro ao ler perfomative no gestor de gares {}".format(msg.sender) + performative)
        else    :
                print("Gestor de Gares Did not received any message after 10 seconds")

'''def gerar_gare():
    tipos = ["comercial", "carga"]
    id_gare = random.randint(1000, 9999)
    tipo = random.choice(tipos)
    #coordenadas X e Y
    posicao_x = random.randint(0, 100)
    posicao_y= random.randint(0, 100)
    return {
        "id": id_gare,
        "tipo": tipo,
        "posicao_x": posicao_x,
        "posicao_y": posicao_y,
        "ocupacao": False
    }'''