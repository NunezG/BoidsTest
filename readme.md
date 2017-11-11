Artificial Intelligence (Boids). CAPTURE THE FLAG. Guillermo Nunez.

**************************************
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

*****

·               On each side: a flag
§  Each team tries to grab the enemy flag and to bring it back to its own flag that must be in its stand in order to score a point.
§  When a lion or an antelope is killed, it reappears to its starting point after a few seconds.

----------------------------------------------

Using Direct2D sample for simplicity.

Planification:

- Use of FSM for main flow and also characters.

- No obstacles are expected so no pathfinding is needed.

- Use of steering Behaviors, such as "Pursue and Evade" or Flocking to simulate herds for antelopes.

- Strategy (aggressivity) for each team needs to be defined, reappearing time is a critical factor. 