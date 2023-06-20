import time
import random 
from spade import quit_spade


from Agents.torrecontrolo import TorreControloAgent
from Agents.gestorgares import GestorGaresAgent
from Agents.aviao import AviaoAgent
from Agents.infovoos import InfoVoosAgent

XMPP_SERVER = 'purp'
PASSWORD = 'admin'


def gerar_aviao():
    companhias = ["Delta", "United", "American Airlines", "Lufthansa", "Emirates"]
    
    tipos = ["comercial", "carga"]
    id_aviao = random.randint(1000, 9999)
    companhia = random.choice(companhias)
    tipo = random.choice(tipos)
    intencao = random.choice(["aterrar", "descolar"])
    if intencao == "aterrar":
        origens = ["Londres", "Braga", "Paris", "Dubai", "São Paulo"]
        destinos = ["Madrid", "Los Angeles", "Roma", "Bangkok", "Braga"]
        origem = random.choice(origens)
        destino = random.choice(destinos)
    else: 
        origem = random.choice(["Londres", "Paris", "Dubai", "São Paulo"])
        destino = "Braga"
        
    return {
        "companhia": companhia,
        "tipo": tipo,
        "id_aviao": id_aviao,
        "origem": origem,
        "destino": destino,
        "intencao": intencao
    }

def gerar_gare():
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
    }

def gerar_pista():
    id_pista = random.randint(1000, 9999)
    posicao_x = random.randint(0, 100)
    posicao_y= random.randint(0, 100)
    return {
        "id_pista": id_pista,
        "posicao_x": posicao_x,
        "posicao_y": posicao_y,
        "ocupacao": False
    }


if __name__ == '__main__':

    agentecontrolo_jid = 'torrecontrolo@'+XMPP_SERVER
    gestorgares_jid = 'gestorgares@'+XMPP_SERVER
    #aviao_jid = 'aviao@'+XMPP_SERVER
    infovoos_jid = 'infovoos@'+XMPP_SERVER

    # create control agents
    torrecontrolo_agent = TorreControloAgent(agentecontrolo_jid, PASSWORD)
    gestorgares_agent = GestorGaresAgent(gestorgares_jid, PASSWORD)
    #aviao_agent = AviaoAgent(aviao_jid, PASSWORD)
    infovoos_agent = InfoVoosAgent(infovoos_jid, PASSWORD)

    res_torre = torrecontrolo_agent.start(auto_register=True)
    res_torre.result()
    res_info = infovoos_agent.start(auto_register=True)
    res_info.result()
    res_gares = gestorgares_agent.start(auto_register=True)
    res_gares.result()

    # print the main agent info
    MAX_AVIOES = 10
    MAX_GARES = 2
    MAX_PISTAS = 2
    lista_gares = [gerar_gare() for _ in range(MAX_GARES)]
    print("GARES:")
    print(len(lista_gares))
    print(lista_gares)
    print("\n")
    lista_pistas = [gerar_pista() for _ in range(MAX_PISTAS)]
    print( "PISTAS:")
    print(len(lista_pistas))
    print(lista_pistas)
    print("\n")
    gestorgares_agent.set("lista_gares", lista_gares)
    gestorgares_agent.set("lista_pistas", lista_pistas)

    avioes_lista = []

    #time.sleep(2)


    # then we start the flight agents
    for i in range(1,MAX_AVIOES+1):
        tempo = random.randint(1, 5)
        aviao_agent = AviaoAgent('aviao'+str(i)+'@'+XMPP_SERVER, PASSWORD)
        aviao_agent.set("torre", agentecontrolo_jid)
        time.sleep(tempo)
        res_aviao = aviao_agent.start()
        
        avioes_lista.append(aviao_agent)
        
        
    '''
    lista_avioes = [gerar_aviao() for _ in range(20)]
    print("AVIOES: ")
    print(len(lista_avioes))
    print(lista_avioes)
    print("\n")
    lista_gares = [gerar_gare() for _ in range(20)]
    print("GARES:")
    print(len(lista_gares))
    print(lista_gares)
    print("\n")
    lista_pistas = [gerar_pista() for _ in range(20)]
    print( "PISTAS:")
    print(len(lista_pistas))
    print(lista_pistas)
    print("\n")
    '''
    #aviao_agent.set("lista_avioes", lista_avioes)
    #gestorgares_agent.set("lista_gares", lista_gares)
    #gestorgares_agent.set("lista_pistas", lista_pistas)
    
    
    #res_gares = gestorgares_agent.start()
   # res_aviao = aviao_agent.start()
    #res_infovoos = infovoos_agent.start()

    #res_torre.result()

    while torrecontrolo_agent.is_alive():
        try:
            time.sleep(1)
        except KeyboardInterrupt:
            for aviao_agent in avioes_lista:
                aviao_agent.stop()

            torrecontrolo_agent.stop()
            
            gestorgares_agent.stop()
            infovoos_agent.stop()
            break
    print("Agentes terminados")

    quit_spade()


#estacionamento

#no começo da gare mandar a informação para a torre



   


