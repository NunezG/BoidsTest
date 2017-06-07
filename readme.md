Ivory Tower test task. Guillaume Nunez.
**************************************

Goal:

Create a mini-game « Capture the flag, Lions VERSUS Antelopes » in C++ :
·         We are interested in the archi, the code
·         We are NOT interested in the look, don’t spend time on graphic/audio
·               ie. no mesh, no anim, no sound
·               in any case if you add some, you won’t be judged on that
·               Something only with ASCII can even do the job! 
·         You can start on any existing free framework : a simple directX sample would be perfect
·         Flow:
·               autonomous, not playable

*****
·               One team of Lions
§  Lions are fewer
§  They go slower
§  But they can kill an antelope in 1V1

*****
·               One team of antelopes
§  Many More
§  They are faster
§  But they can only kill a lion in 4V1
§  They are gregarious
·               On each side: a flag
§  Each team tries to grab the enemy flag and to bring it back to its own flag that must be in its stand in order to score a point.
§  When a lion or an antelope is killed, it reappears to its starting point after a few seconds.
·         We are interested to see in the code:
·               classes, OOP, inheritance ...
·               FSM that manages the general flow
·               Managers of objects that manage the lifecycle of objects
·               A minimum of dynamic on objects
·               A minimum of AI on objects
·               The content and the form of the code are important
·               The overall can be small and simple
·         All the rest is plus ;) …


----------------------------------------------

Using Direct2D sample for simplicity.

Planification:

- Use of FSM for main flow and also characters.

- No obstacles are expected so no pathfinding is needed.

- Use of steering Behaviors, such as "Pursue and Evade" or Flocking to simulate herds for antelopes.

- Strategy (aggressivity) for each team needs to be defined, reappearing time is a critical factor. 