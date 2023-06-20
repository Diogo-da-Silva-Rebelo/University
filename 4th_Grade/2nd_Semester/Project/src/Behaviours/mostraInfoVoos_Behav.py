import jsonpickle
from spade.behaviour import CyclicBehaviour
from spade.message import Message

from Classes.informaviao import InformAviao



class MostraInfoVoos_Behav(CyclicBehaviour):
    def __init__(self):
        super().__init__()
        self.chegadas = []
        self.partidas = []
       
        #self.time_converter = TimeConverter(conversion_rate=1800)

    async def run(self):
        msg = await self.receive(timeout=10)
        if msg:
            performative = msg.get_metadata('performative')
            if performative == 'inform':
                aviao_reg = jsonpickle.decode(msg.body)
                if aviao_reg.get_intencao() == 'aterrar':
                    if aviao_reg not in self.chegadas:  # Verifica se o avião já está na lista
                        self.chegadas.append(aviao_reg)
                elif aviao_reg.get_intencao() == 'descolar':
                    if aviao_reg not in self.partidas:  # Verifica se o avião já está na lista
                        self.partidas.append(aviao_reg)
            else:
                print("Mensagem recebida não tem o tipo 'inform'")
        else:
            print("Agente {} não recebeu nenhuma mensagem após 10 segundos".format(str(self.agent.jid)))

        # remover duplicados
        self.chegadas = list(dict.fromkeys(self.chegadas))
        self.partidas = list(dict.fromkeys(self.partidas))
        
        # Imprimir tabela de chegadas
        print("\n")
        print("<--------- Informação Geral Voos --------->")
        print("Chegadas")
        
        print("{:<20} {:<20} {:<10} {:<10}".format("ID", "Companhia", "Origem", "Tipo"))
        
        for aviao in self.chegadas:
            id_aviao = aviao.get_id_aviao()
            companhia = aviao.get_companhia()
            origem = aviao.get_origem()
            tipo = aviao.get_tipo()
            #tempo = self.time_converter.simulated_to_real(aviao.get_chegada())
            #hora = tempo.strftime("%H:%M")
            if aviao.get_atrasado() == '1':
                print("{:<20} {:<20} {:<10} {:<10} ATRASADO".format(id_aviao, companhia, origem, tipo))
            elif aviao.get_atrasado() == '0':
                print("{:<20} {:<20} {:<10} {:<10}".format(id_aviao, companhia, origem, tipo))
            else:
                print("{:<20} {:<20} {:<10} {:<10} MUDANÇA AEROPORTO".format(id_aviao, companhia, origem, tipo))
        print("\n")
        # Imprimir tabela de partidas
        print("Partidas")
        #print do self.partidas

        print("{:<20} {:<20} {:<10} {:<10}".format("ID", "Companhia", "Destino", "Tipo"))
        for aviao in self.partidas:
            id_aviao = aviao.get_id_aviao()
            companhia = aviao.get_companhia()
            destino = aviao.get_destino()
            tipo = aviao.get_tipo()
            #tempo = self.time_converter.simulated_to_real(aviao.get_partida())
            #hora = tempo.strftime("%H:%M")
            if aviao.get_atrasado() == '1':
                print("{:<20} {:<20} {:<10} {:<10} ATRASADO".format(id_aviao, companhia, destino, tipo))
            elif aviao.get_atrasado() == '0':
                print("{:<20} {:<20} {:<10} {:<10}".format(id_aviao, companhia, destino, tipo))
            else:
                print("{:<20} {:<20} {:<10} {:<10} MUDANÇA AEROPORTO".format(id_aviao, companhia, destino, tipo))
        print("\n")
       
