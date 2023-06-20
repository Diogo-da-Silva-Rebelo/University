from spade import agent

from Behaviours.enviaRespostaGare_Behav import EnviaRespostaGare_Behav

class GestorGaresAgent(agent.Agent):
    async def setup(self):
        print("Gare Agent Started")
        a = EnviaRespostaGare_Behav()
        self.add_behaviour(a)