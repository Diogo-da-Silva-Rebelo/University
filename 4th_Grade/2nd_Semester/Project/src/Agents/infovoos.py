from spade import agent

from Behaviours.mostraInfoVoos_Behav import MostraInfoVoos_Behav

class InfoVoosAgent(agent.Agent):
    async def setup(self):
        print("InfoVoos Agent Started")
        a = MostraInfoVoos_Behav()


        self.add_behaviour(a)