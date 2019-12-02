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
+ Click "revive" when dead.


## How it Works.
### Game coordinates.
The game uses three different coordinates and I will call them "World coordinates", "city coordinates" and "screen coordinates".  
The screen coordinates as the name indicates are the window coordinates with the origin (0,0) being at the top left corner. The function used in the bot for the right click mouse uses this coordinate as parameters.  
A world coordinate is a pair of integers for every point in the world of the game. The monsters coordinates the bots extracts from memory are stored in this coordinate format.  
Finally, a city coordinate is the coordinate that you see written on top of the game screen which is unique for every point in the city only. The jump function the bot used uses this coordinate format.  
One thing to notice is that world coordinates and city coordinates are not parallel to the screen coordinates.  

After collecting some data I found that

<img src="https://latex.codecogs.com/gif.latex?\small&space;\textbf{Relative&space;screen&space;coordinates&space;}&space;=&space;A&space;\left(\textbf{Relative&space;world&space;coordinates&space;}\right)&space;&plus;&space;(290,400)" title="\small \textbf{Relative screen coordinates } = A \left(\textbf{Relative world coordinates }\right) + (290,400)" />

where A is the rotation by 45 degree operator.
Relative screen coordinates = monster screen coordinates - player screen coordinates
Relative world coordinates = monster world coordinates - player world coordinates

As for the city coordinates and world coordinates, I used the quick approximate result that I found

<img src="https://latex.codecogs.com/gif.latex?\small&space;\textbf{Relative&space;citycoordinates&space;}&space;=&space;\frac{2}{100}\left(\textbf{Relative&space;world&space;coordinates&space;}\right)" title="\small \textbf{Relative citycoordinates } = \frac{2}{100}\left(\textbf{Relative world coordinates }\right)" />


## Filling Curiosity and some statistics.
### Record damages
I wanted to know how the damage written on the status is related to the damage shown when hitting a monster. This is why I created this bot originally. You will find a script named "Record damages", when run it will inject a code to the place where the damage is subtracted from the monster health (surprisingly to me, this worked only for close range weapons. the bow has a different place and even a skill such as "scatter" has an even different place). This code will create a file named `damages.txt` in the game folder which will contain the damages recorded (when I hit monsters, I some times see knd of low damages which confused me and made me curious and started this project, however it turns out that this damage is not recorded by the "Record damages" script ! Nice coincidence, it is probably a result of some supportive skill or something, to find out later).  
The injected code is a simple "fopen", "fprintf" and "fclose" as you can check it. The collected data can be found in this folder as well, they are named `38-72.txt` and `179-492.txt`. The names indicate the upper attack bound and the lower attack bound. The data in the files are numbers separated by one "new line" each, and there is an additional "new line" at the end of the files.

### Observations
Plotting the data we see some kind of uniformity (although, I imagine it would be normal).
<p, align=center>
[Imgur](https://i.imgur.com/97aCAyv.png)
</p>
