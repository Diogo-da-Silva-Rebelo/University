from spade.behaviour import CyclicBehaviour
from spade.message import Message

class RecebeConfirmacao_Behav(CyclicBehaviour):
    async def run(self):
        msg = await self.receive(timeout=10)  # wait for a message for 10 seconds
        if msg:
            # Message Threatment based on different Message performatives
            performative = msg.get_metadata("performative")
            if performative == "confirm":
                print("Agent {}:".format(str(self.agent.jid)) + " Aviao completed!")
                
            elif performative == "refuse":
                print("Agent {}:".format(str(self.agent.jid)) + " Outro aeroporto")
            else:
                print("Agent {}:".format(str(self.agent.jid)) + " Message nao entendida")

            self.kill()  # kill the ReplyBehav

        else:
            print("Agent {}:".format(str(self.agent.jid)) + "Did not received any message after 10 seconds")

    async def on_end(self):  # on ReplyBehav end, kill the respective Customer Agent
        print("Agent {}:".format(str(self.agent.jid)) + " terminating...")
        await self.agent.stop()
