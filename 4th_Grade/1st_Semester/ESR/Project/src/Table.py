import Globals

"""
    table:
        {
            "primary":
                {
                    "next_hop":"$ip",
                    "cost":"$cost",
                },
            "secondary":
                {
                    "next_hop":"$ip",
                    "cost":"$cost",
                }
        }
    """
    
class Table:
    DEFAULT_PORT = 65432
    DEFAULT_ANNOUNCEMENT_PORT = 23456
    
    def __init__(self):
        self.table = {"primary":{"next_hop":None,"cost":None},"secondary":{"next_hop":None,"cost":None}}
                
    def getTable(self):
        return self.table
    
    def getNextHop(self):
        return self.table["primary"]["next_hop"]
    
    def getSecHop(self):
        return self.table["secondary"]["next_hop"]
        
    # addr -> de onde veio a nova table
    # host -> self ip
    def updateTable(self,next_hop,cost):
        toChange = 0
        if self.hasRoute():
            # verificar se o ip encontra na tabela, e atualizar o cost caso seja esse o caso
            if self.table["primary"]["next_hop"] == next_hop:
                if self.table["primary"]["cost"] > cost:
                    self.table["primary"]["cost"] = cost
                    toChange = 1
                
            elif self.table["secondary"]["next_hop"] == next_hop:
                if self.table["secondary"]["cost"] > cost:
                    self.table["secondary"]["cost"] = cost
                    toChange = 2
            
            # caso não haja secundário, preenche
            # caso não se verifique, verificar para o secundário e subsituir caso compense
            elif self.table["secondary"]["next_hop"] is None or cost < self.table["secondary"]["cost"]:
                self.table["secondary"]["next_hop"] = next_hop
                self.table["secondary"]["cost"] = cost
                toChange = 2
                
            # ordenar a tabela por ordem de menor cost
            if toChange != 0:
                # secundário melhor que primário
                if self.table["secondary"]["cost"] < self.table["primary"]["cost"]:
                    self.changeOrder()
                    toChange = 1

        else:
            self.table["primary"]["next_hop"] = next_hop
            self.table["primary"]["cost"] = cost
            toChange = 1
        return toChange
        
    def hasRoute(self):
        return self.table["primary"]["next_hop"]
    
    def removePrimaryRoute(self):
        self.table["primary"]["next_hop"] = None
        self.table["primary"]["cost"] = None
        self.changeOrder()
    
    def removeSecondaryRoute(self):
        self.table["secondary"]["next_hop"] = None
        self.table["secondary"]["cost"] = None
    
    def getSecondRouteCost(self):
        return self.table["secondary"]["cost"]
    
    def getRouteCost(self):
        return self.table["primary"]["cost"]
    
    def changeOrder(self):
        temp = self.table["primary"]
        self.table["primary"] = self.table["secondary"]
        self.table["secondary"] = temp
        
    def print(self):
        print(20*'*' + ' TABLE ' + 20*'*')
        globals.printDebug("Rota Primaria:\n\tnext_hop: ",end="")
        if self.table["primary"]["next_hop"]:
            globals.printSuccess(str(self.table["primary"]["next_hop"]))
            globals.printDebug("\tcost: ",end="")
            globals.printSuccess(str(self.table["primary"]["cost"]))
        else:
            globals.printError("None")
            globals.printDebug("\tcost: ",end="")
            globals.printError("None")
        
        globals.printDebug("Rota Secundaria:\n\tnext_hop: ",end="")
        if self.table["secondary"]["next_hop"]:
            globals.printSuccess(str(self.table["secondary"]["next_hop"]))
            globals.printDebug("\tcost: ",end="")
            globals.printSuccess(str(self.table["secondary"]["cost"]))
        else:
            globals.printError("None")
            globals.printDebug("\tcost: ",end="")
            globals.printError("None")
        print(40*'*')