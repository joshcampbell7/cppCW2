/*
    Main Engine handles the actual playing of the text adventure game.
    The different text based commands are handled in this file
 */

#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <fstream>
#include "MainEngine.h"
#include "Player.h"
#include "jsonParser.h"
#include "Map.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

//method for moving between rooms
string goMethod(const vector<string> &command, Map &gameMap) {
    //if the room is one of the exits then move the player to that room
    if (gameMap.getPlayer().getCurrentRoom().getExits().find(command.at(1)) !=
        gameMap.getPlayer().getCurrentRoom().getExits().end()) {
        //if enemies are still alive in the room you are leaving then there is a chance you will be attacked
        if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
            int random = rand() % 100 + 1;
            Enemy enemy = gameMap.getPlayer().getCurrentRoom().getEnemies().at(0);
            if (enemy.getAggressiveness() > random) {
                gameMap.getPlayer().setHealth(gameMap.getPlayer().getHealth() - enemy.getAggressiveness());
                if (gameMap.getPlayer().getHealth() <= 0) {
                    return "You tried to leave the room but " + enemy.getEnemyName() +
                           " attacked you and you are now DEAD!! ";
                }
                cout << "You tried to leave the room but " << enemy.getEnemyName()
                     << " attacked you and your new health is: " << to_string(gameMap.getPlayer().getHealth())
                     << ". You escaped just in time." << endl;
            }
        }
        Room &nextRoom = gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getExits().at(command.at(1)));
        gameMap.getPlayer().setCurrentRoom(nextRoom);
        //if the new room is in the list of objectives then remove it form the list
        if (gameMap.getObjective().getType() == "room") {
            for (string i: gameMap.getObjective().getWhat()) {
                if (i == nextRoom.getRoomId()) {
                    gameMap.getObjective().removeWhat(i);
                }
            }
        }
        //give description, objects, and enemies of the new room
        cout << "Travelling " << command.at(1) << "..." << endl;
        cout << "\nYou now find yourself in " + gameMap.getPlayer().getCurrentRoom().getRoomId() + ". " +
                gameMap.getPlayer().getCurrentRoom().getDescription();
        if (!gameMap.getPlayer().getCurrentRoom().getObjects().empty()) {
            cout << "\nIn this room you can see some objects: ";
            for (Object i: gameMap.getPlayer().getCurrentRoom().getObjects()) {
                cout << i.getObjectName();
            }
            if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
                cout << "\n...and some enemies: ";
            }
        } else if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
            cout << "\nIn this room you can see some enemies: ";
        }
        for (Enemy i: gameMap.getPlayer().getCurrentRoom().getEnemies()) {
            cout << i.getEnemyName();
        }
        cout << endl;
        return "";
    }
    return "You can't go that way...";
}

//method for taking objects
string takeMethod(const vector<string> &command, Map &gameMap) {
    vector<Object> objectsInRoom = gameMap.getPlayer().getCurrentRoom().getObjects();
    for (Object object: objectsInRoom) {
        //if the object is found in the room then add it to the inventory and remove it form the room
        if (object.getObjectName() == command.at(1)) {
            gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getRoomId()).removeObjects(object);
            gameMap.getPlayer().getCurrentRoom().removeObjects(object);
            gameMap.getPlayer().addObjects(object);
            //if the object is in the list of objectives then remove it from the list
            if (gameMap.getObjective().getType() == "collect") {
                for (string i: gameMap.getObjective().getWhat()) {
                    if (i == object.getObjectName()) {
                        gameMap.getObjective().removeWhat(i);
                    }
                }
            }
            return object.getObjectName() + " item added to inventory.";
        }
    }
    return "That item isn't in the room...";
}

//method for looking
string lookMethod(const vector<string> &command, Map &gameMap) {
    //look/list items will list all the items in the player's inventory
    if (command.at(1) == "items") {
        if (gameMap.getPlayer().getObjects().empty()) {
            return "You do not currently possess any items.\n";
        }
        cout << "You are in possession of the following items: " << endl;
        for (Object &object: gameMap.getPlayer().getObjects()) {
            cout << object.getObjectName() << endl;
        }
        return "";
    }
    //give description of object if it is in the room
    for (Object &object: gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getRoomId()).getObjects()) {
        if (command.at(1) == object.getObjectName()) {
            return object.getDescription() + " Be sure to take it first though...";
        }
    }
    //give description of object if it is in the player's inventory
    for (Object &object: gameMap.getPlayer().getObjects()) {
        if (command.at(1) == object.getObjectName()) {
            return object.getDescription() + " Be sure to take it first though...";
        }
    }
    return "That object is not in this room...";
}

//method for attacking enemies
string killMethod(const vector<string> &command, Map &gameMap) {
    vector<Enemy> enemiesInRoom = gameMap.getPlayer().getCurrentRoom().getEnemies();
    for (Enemy enemy: enemiesInRoom) {
        //if the enemy is in the room then you can attack it
        if (enemy.getEnemyName() == command.at(1)) {
            bool weapon = false;
            //check if you have the correct weapon to kill it in your inventory
            for (const Object &object: gameMap.getPlayer().getObjects()) {
                for (const string &killer: enemy.getKilledBy()) {
                    if (killer == object.getObjectName()) {
                        weapon = true;
                        break;
                    }
                }
                if (weapon) {
                    break;
                }
            }
            if (enemy.getKilledBy().empty()) {
                weapon = true;
            }
            //if you have the correct weapon then the enemy is removed from the room (killed)
            if (weapon) {
                gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getRoomId()).removeEnemies(enemy);
                gameMap.getPlayer().getCurrentRoom().removeEnemies(enemy);
                //if the enemy is in the list of objectives then remove it form the list
                if (gameMap.getObjective().getType() == "kill") {
                    for (string i: gameMap.getObjective().getWhat()) {
                        if (i == enemy.getEnemyName()) {
                            gameMap.getObjective().removeWhat(i);
                        }
                    }
                }
                //add health back to the player as a reward for killing the enemy
                gameMap.getPlayer().setHealth(gameMap.getPlayer().getHealth() + enemy.getAggressiveness());
                return enemy.getEnemyName() +
                       " has been killed. They dropped a potion that replenished your health, your new health is " +
                       to_string(gameMap.getPlayer().getHealth());
            } else {
                //the player doesn't have the correct weapon so their health is reduced
                gameMap.getPlayer().setHealth(gameMap.getPlayer().getHealth() - enemy.getAggressiveness());
                if (gameMap.getPlayer().getHealth() <= 0) {
                    return "You don't have the right weapon to kill " + enemy.getEnemyName() +
                           "... it attacked you and you are now DEAD!! ";
                }
                return "You don't have the right weapon to kill " + enemy.getEnemyName() +
                       "... it attacked you and your new health is: " + to_string(gameMap.getPlayer().getHealth());
            }
        }
    }
    return "That enemy isn't in this room...";
}

//method to save the game
string saveMethod(const vector<string> &command, Map &gameMap) {
    ofstream file("saveGame.json");
    json data = formatJson(gameMap);

    if (file.is_open()) {
        file << data.dump(2);
        file.close();
        return "Game has been saved!";
    } else {
        throw runtime_error("ERROR IN MainEngine.cpp, Failed to save json: File did not open ");
    }
}

void moveHandler(Map &gameMap) {
    //enum and map set up to facilitate use of switch case statements as they can't handle strings
    enum moveCode {
        mGo, mTake, mLook, mKill, mSave
    };
    map<string, moveCode> m = {{"look", mLook},
                               {"list", mLook},
                               {"go",   mGo},
                               {"move", mGo},
                               {"take", mTake},
                               {"save", mSave},
                               {"kill", mKill}};

    cout << "\nYou have 4 input command options: go, look, take, fight." << endl;
    cout << "\nYou begin your adventure in " + gameMap.getPlayer().getCurrentRoom().getRoomId() + ". " +
            gameMap.getPlayer().getCurrentRoom().getDescription() << endl;

    //list objects and enemies in the initial room
    if (!gameMap.getPlayer().getCurrentRoom().getObjects().empty()) {
        cout << "In this room you can see some objects: ";
        for (Object i: gameMap.getPlayer().getCurrentRoom().getObjects()) {
            cout << i.getObjectName();
        }
        cout << endl;
        if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
            cout << "...and some enemies: ";
        }
    } else if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
        cout << "In this room you can see some enemies: ";
    }
    for (Enemy i: gameMap.getPlayer().getCurrentRoom().getEnemies()) {
        cout << i.getEnemyName();
    }
    cout << endl;

    //accept user input until the objective3 has been met or the player has run out of health
    while (!gameMap.getObjective().getWhat().empty() && gameMap.getPlayer().getHealth() > 0) {
        //input stream needs to be cleared before using the getline function
        cin.clear();
        cin.sync();
        string userAction;
        getline(cin, userAction);
        string s1;
        istringstream iss(userAction);
        vector<string> command;

        //splits the input string into first word and remaining words (has size of 2)
        iss >> s1;
        command.push_back(s1);
        if (iss) {
            string s2;
            getline(iss, s2);
            if (s2.size() > 1) {
                command.push_back(s2.substr(1));
            }
        }

        //checks if command given is one of the valid commands in the map
        if (m.find(command.at(0)) == m.end()) {
            cout << "Please enter a valid input." << endl;
            continue;
        }

        //runs relevant method for given input
        //each case handles incorrect input
        switch (m.at(command.at(0))) {
            case mGo:
                if (command.size() < 2) {
                    cout << "Go where?" << endl;
                    break;
                }
                cout << goMethod(command, gameMap) << endl;
                break;
            case mTake:
                if (command.size() < 2) {
                    cout << "Take what?" << endl;
                    break;
                }
                cout << takeMethod(command, gameMap) << endl;
                break;
            case mLook:
                //gives information on room, objects, and enemies when nothing is specified to look at
                if (command.size() < 2) {
                    cout << "\nYou are currently in " + gameMap.getPlayer().getCurrentRoom().getRoomId() + ". " +
                            gameMap.getPlayer().getCurrentRoom().getDescription() << endl;
                    if (!gameMap.getPlayer().getCurrentRoom().getObjects().empty()) {
                        cout << "In this room you can see some objects: ";
                        for (Object i: gameMap.getPlayer().getCurrentRoom().getObjects()) {
                            cout << i.getObjectName();
                        }
                        cout << endl;
                        if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
                            cout << "...and some enemies: ";
                        }
                    } else if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
                        cout << "In this room you can see some enemies: ";
                    }
                    for (Enemy i: gameMap.getPlayer().getCurrentRoom().getEnemies()) {
                        cout << i.getEnemyName();
                    }
                    break;
                }
                cout << lookMethod(command, gameMap) << endl;
                break;
            case mKill:
                if (command.size() < 2) {
                    cout << "Kill what?" << endl;
                    break;
                }
                cout << killMethod(command, gameMap) << endl;
                break;
            case mSave:
                cout << saveMethod(command, gameMap) << endl;
                exit(0);
            default:
                cout << "Please enter a valid input." << endl;
                break;
        }
    }
}

void mainEngine(Map &gameMap) {
    cout << "Welcome to The Text Adventure Game" << endl;
    cout << "Welcome player!, you have " + to_string(gameMap.getPlayer().getHealth()) +
            " health to start with. " + "You also have " + to_string(gameMap.getPlayer().getObjects().size()) +
            " objects in your inventory." << endl;

    //introduce the objective
    if (gameMap.getObjective().getType() == "kill") {
        cout << "\nTo win the game, your objective is to kill the following enemies: " << endl;
        for (string i: gameMap.getObjective().getWhat()) {
            cout << i << endl;
        }
    }
    if (gameMap.getObjective().getType() == "collect") {
        cout << "\nTo win the game, your objective is to collect the following items: " << endl;
        for (string i: gameMap.getObjective().getWhat()) {
            cout << i << endl;
        }
    }
    if (gameMap.getObjective().getType() == "room") {
        cout << "\nTo win the game, your objective is to visit the following rooms: " << endl;
        for (string i: gameMap.getObjective().getWhat()) {
            cout << i << endl;
        }
    }

    //call method that handles the user inputs etc
    moveHandler(gameMap);
    if (gameMap.getPlayer().getHealth() > 0) {
        cout << "Congratulations! YOU WIN!!!" << endl;
    } else {
        cout << "Out of health! You lose!!! :(" << endl;
    }
}
