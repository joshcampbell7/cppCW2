/*
    Main Engine handles the actual playing of the text adventure game.
    The different text based commands are handled in this file
 */

#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include "MainEngine.h"
#include "Player.h"
#include "jsonParser.h"
#include "Map.h"

using namespace std;

string goMethod(const vector<string> &command, Map &gameMap) {
    if (gameMap.getPlayer().getCurrentRoom().getExits().find(command.at(1)) !=
        gameMap.getPlayer().getCurrentRoom().getExits().end()) {
        Room &nextRoom = gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getExits().at(command.at(1)));
        gameMap.getPlayer().setCurrentRoom(nextRoom);
        cout << "\nYou now find yourself in " + gameMap.getPlayer().getCurrentRoom().getRoomId() + ". " +
                gameMap.getPlayer().getCurrentRoom().getDescription() << endl;
        if (!gameMap.getPlayer().getCurrentRoom().getObjects().empty()) {
            cout << "In this room you can see some objects: ";
            for (Object i: gameMap.getPlayer().getCurrentRoom().getObjects()) {
                cout << i.getObjectName();
            }
            if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
                cout << "...and some enemies: ";
            }
        } else if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
            cout << "In this room you can see some enemies: ";
        }
        for (Enemy i : gameMap.getPlayer().getCurrentRoom().getEnemies()) {
            cout << i.getEnemyName();
        }
        cout << endl;
        if (gameMap.getObjective().getType() == "room") {
            for (string i : gameMap.getObjective().getWhat()) {
                if (i == nextRoom.getRoomId()) {
                    gameMap.getObjective().removeWhat(i);
                }
            }
        }
        return "Travelling " + command.at(1) + "...";
    }
    return "You can't go that way...";
}

string takeMethod(const vector<string> &command, Map &gameMap) {
    vector<Object> objectsInRoom = gameMap.getPlayer().getCurrentRoom().getObjects();
    for (Object object: objectsInRoom) {
        if (object.getObjectName() == command.at(1)) {
            gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getRoomId()).removeObjects(object);
            gameMap.getPlayer().getCurrentRoom().removeObjects(object);
            gameMap.getPlayer().addObjects(object);
            if (gameMap.getObjective().getType() == "collect") {
                for (string i : gameMap.getObjective().getWhat()) {
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

string lookMethod(const vector<string> &command, Map &gameMap) {
    for (Object &object: gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getRoomId()).getObjects()) {
        if (command.at(1) == object.getObjectName()) {
            return object.getDescription() + " Be sure to take it first though...";
        }
    }
    return "That object is not in this room...";
}

string killMethod(const vector<string> &command, Map &gameMap) {
    vector<Enemy> enemiesInRoom = gameMap.getPlayer().getCurrentRoom().getEnemies();
    for (Enemy enemy: enemiesInRoom) {
        if (enemy.getEnemyName() == command.at(1)) {
            bool weapon = false;
            for (const Object& object : gameMap.getPlayer().getObjects()) {
                for (const string& killer : enemy.getKilledBy()) {
                    if (killer == object.getObjectName()) {
                        weapon = true;
                        break;
                    }
                }
                if (weapon) {
                    break;
                }
            }
            if (weapon) {
                gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getRoomId()).removeEnemies(enemy);
                gameMap.getPlayer().getCurrentRoom().removeEnemies(enemy);
                if (gameMap.getObjective().getType() == "kill") {
                    for (string i : gameMap.getObjective().getWhat()) {
                        if (i == enemy.getEnemyName()) {
                            gameMap.getObjective().removeWhat(i);
                        }
                    }
                }
                return enemy.getEnemyName() + " has been killed.";
            } else {
                gameMap.getPlayer().setHealth(gameMap.getPlayer().getHealth() - enemy.getAggressiveness());
                if(gameMap.getPlayer().getHealth() <=0){
                    return "You don't have the right weapon to kill " + enemy.getEnemyName() + "... it attacked you and you are now DEAD!! ";
                }
                return "You don't have the right weapon to kill " + enemy.getEnemyName() + "... it attacked you and your new health is: " + to_string(gameMap.getPlayer().getHealth());

            }
        }
    }
    return "That enemy isn't in this room...";
}

void moveHandler(Map &gameMap) {
    //enum and map set up to facilitate use of switch case statements as they can't handle strings
    enum moveCode {
        mGo, mTake, mLook, mKill
    };
    map<string, moveCode> m = {{"look", mLook},
                               {"go",   mGo},
                               {"move", mGo},
                               {"take", mTake},
                               {"kill", mKill}};

    cout << "\nYou have 4 input command options: go, look, take, fight." << endl;
    cout << "\nYou begin your adventure in " + gameMap.getPlayer().getCurrentRoom().getRoomId() + ". " +
            gameMap.getPlayer().getCurrentRoom().getDescription() << endl;
    if (!gameMap.getPlayer().getCurrentRoom().getObjects().empty()) {
        cout << "In this room you can see some objects: ";
        for (Object i: gameMap.getPlayer().getCurrentRoom().getObjects()) {
            cout << i.getObjectName();
        }
        if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
            cout << "...and some enemies: ";
        }
    } else if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
        cout << "In this room you can see some enemies: ";
    }
    for (Enemy i : gameMap.getPlayer().getCurrentRoom().getEnemies()) {
        cout << i.getEnemyName();
    }
    cout << endl;
    while (!gameMap.getObjective().getWhat().empty()) {
        //input stream needs to be cleared before using the getline function
        cin.clear();
        cin.sync();
        string userAction;
        string s1;
        istringstream iss(userAction);
        vector<string> command;

        //splits the input string into first word and remaining words
        getline(cin, userAction);
        iss >> s1;
        command.push_back(s1);
        if (iss) {
            string s2;
            getline(iss, s2);
            command.push_back(s2);
        }
        //checks for valid input command
        /*
        if (m.find(command.at(0)) == m.end()) {
            cout << "Please enter a valid input." << endl;
            continue;
        }
         */
        cout << command.at(0);
        //runs relevant method for given input
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
                if (command.size() < 2) {
                    if (!gameMap.getPlayer().getCurrentRoom().getObjects().empty()) {
                        cout << "In this room you can see some objects: ";
                        for (Object i: gameMap.getPlayer().getCurrentRoom().getObjects()) {
                            cout << i.getObjectName();
                        }
                        if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
                            cout << "...and some enemies: ";
                        }
                    } else if (!gameMap.getPlayer().getCurrentRoom().getEnemies().empty()) {
                        cout << "In this room you can see some enemies: ";
                    }
                    for (Enemy i : gameMap.getPlayer().getCurrentRoom().getEnemies()) {
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
            default:
                cout << "Please enter a valid input." << endl;
                break;
        }
    }
}

void mainEngine(Map &gameMap) {
    cout << "Welcome to Map .. of Text Adventure Game" << endl;
    /*
    cout << "Before we start, What is your name?" << endl;
    string name;
    cin >> name;

    cout << "Welcome " + player.getPlayerName() + "!, " + "you have " + to_string(player.getHealth()) +
            " health to start with. " + "You also have " + to_string(player.getObjects().size()) +
            " objects in your inventory." << endl;
    */
    cout << "Welcome player!, you have " + to_string(gameMap.getPlayer().getHealth()) +
            " health to start with. " + "You also have " + to_string(gameMap.getPlayer().getObjects().size()) +
            " objects in your inventory." << endl;

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

    //Add code to handle other objects

    //call method that handles the user inputs etc
    moveHandler(gameMap);
    if (gameMap.getPlayer().getHealth())
    cout << "Congratulations! YOU WIN!!!" << endl;
}
