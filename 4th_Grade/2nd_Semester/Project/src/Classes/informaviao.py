class InformAviao:
    def __init__(self, id_aviao, companhia, origem, destino, tipo, intencao,atrasado,pista=None,gare=None):
        self.id_aviao = id_aviao
        self.companhia = companhia
        self.origem = origem
        self.destino = destino
        self.tipo = tipo
        self.intencao = intencao
        self.atrasado = atrasado
        self.pista = pista
        self.gare = gare

    def get_id_aviao(self):
        return self.id_aviao
    
    def get_companhia(self):
        return self.companhia
    
    def get_origem(self):
        return self.origem
    
    def get_destino(self):
        return self.destino
    
    def get_tipo(self):
        return self.tipo
    
    def get_intencao(self):
        return self.intencao
    
    def get_atrasado(self):
        return self.atrasado
    
    def set_atrasado(self,atraso):
        self.atrasado = atraso
    
    def get_pista(self):
        return self.pista
    
    def set_pista(self,pista):
        self.pista = pista

    def get_gare(self):
        return self.gare
    
    def set_gare(self,gare):
        self.gare = gare
        
    def toStr(self):
        return "Aviao {} da companhia {} de tipo {} irá {} de {} para {}".format(self.id_aviao, self.companhia, self.tipo, self.intencao, self.origem, self.destino)

    
        


        '''
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
        "id": id_aviao,
        "companhia": companhia,
        "origem": origem,
        "destino": destino,
        "tipo": tipo,
        "intencao": intencao
    }'''
