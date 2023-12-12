# C++ CW2 Text Adventure game
Text based adventure game that is compatible with 4 maps
1. Map1.json
2. Map2.json
3. Map3.json
4. Map4.json

## Features

- Player health bar that can vary if attacked by enemy - 
if you try to kill enemy without a valid weapon or leave a room without killing the enemy
you may take damage!
- Save and Load game
- Replenished health after killing enemies


## How to compile using make
1. Navigate to cppCW2 directory and ensure makefile is present
2. run ``make`` in your terminal
3. A file called ``main`` will be generated.
4. To run the application enter the following command ``./main <json map>``

For example to run map1, the command is ``./main map1.json``


## How to save game

To save game run the command ``save`` in the game terminal, this will save the
current state of your game in a json file called `saveGame.json`

## How to load game

To load game run the command in the terminal ``./main saveGame.json``, this will load the
saved changes.

**Note**: **If you save, your previous save will be overwritten**