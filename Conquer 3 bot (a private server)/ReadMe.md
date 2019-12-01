This is a kind of scratch version, but works properly.
This bot uses a monster name and a three points in the map.


## How to use it.
+ Run the script "successful_and_failed_jump"
+ Run the script "auto attack wingedSnake with skill"
+ The monster name can be changed at lines 460 and 521 of the "auto attack wingedSnake with skill" script.
+ The three predetermined point in map can be changed at line 191 of the "auto attack wingedSnake with skill" script, which has the label "given_points".
+ To avoid the usual message that asks you press a button to confirm you are a human run the program "Auto click No button". It will look for the game window and keep enumerating the children windows. Whenever it find a window with caption "No", it will send a click message ( BM_CLICK ) to it.
+ To stop the the bot change the value of the variable "kill_thread" to 1. Killing the thread will start once its value becomes 200.


## Issues.
+ High jumps sometimes which results in sever disconnection.
To resolve it, additional variable "changeCityLocalCoord" has been introduced by injecting code into the function the changes the "city coordinates" to wait for the change after the jump before asking for a new jump using the old coordinates.


## Improvement/To Do.
+ Avoid very strong monsters, which have very long health (over some millions). An idea to calculate the mean of monsters coordinates in four different directions and choosing the one with highest number of monsters that does not get too close to strong monsters.
(this is why you will see labels like "monster_mean_world_coords_q1_1").


## How it Works.
### Game coordinates.
The game uses three different coordinates and I will call them "World coordinates", "city coordinates" and "screen coordinates".
The screen coordinates 


