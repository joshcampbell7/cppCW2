//
// Created by joshu on 30/11/2023.
//

#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include "MainEngine.h"
#include "Player.h"
#include "jsonParser.h"
#include "Map.h"

using namespace std;

string goMethod(const vector<string> &command, Map &gameMap, bool &newRoom) {
    if (gameMap.getPlayer().getCurrentRoom().getExits().find(command.at(1)) !=
        gameMap.getPlayer().getCurrentRoom().getExits().end()) {
        Room &nextRoom = gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getExits().at(command.at(1)));
        gameMap.getPlayer().setCurrentRoom(nextRoom);
        newRoom = true;
        return "Travelling " + command.at(1) + "...";
    }
    newRoom = false;
    return "Please enter a valid direction.";
}

string takeMethod(const vector<string> &command, Map &gameMap) {
    vector<Object> objectsInRoom = gameMap.getPlayer().getCurrentRoom().getObjects();
    for (Object object: objectsInRoom) {
        if (object.getObjectName() == command.at(1)) {
            gameMap.getRooms().at(gameMap.getPlayer().getCurrentRoom().getRoomId()).removeObjects(object);
            gameMap.getPlayer().getCurrentRoom().removeObjects(object);
            gameMap.getPlayer().addObjects(object);
            return object.getObjectName() + " item added to inventory";
        }
    }
    return "That item isn't in the room.";
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

    return "This is the kill method.";
}

void moveHandler(Map &gameMap) {
    //enum and map set up to facilitate use of switch case statements as they can't handle strings
    enum moveCode {
        mGo, mTake, mLook, mKill
    };
    map<string, moveCode> m = {{"look", mLook},
                               {"go",   mGo},
                               {"take", mTake},
                               {"kill", mKill}};

    cout << "\nYou have 4 input command options: go, look, take, fight." << endl;
    bool newRoom = true;
    while (!gameMap.getObjective().getWhat().empty()) {
        if (newRoom) {
            cout << "\nYou are currently in " + gameMap.getPlayer().getCurrentRoom().getRoomId() + ". " +
                    gameMap.getPlayer().getCurrentRoom().getDescription() << endl;
            newRoom = false;
        }
        //input stream needs to be cleared before using the getline function
        cin.clear();
        cin.sync();
        string userAction;
        getline(cin, userAction);
        //splits the input string by the space character
        string s;
        stringstream ss(userAction);
        vector<string> command;
        while (getline(ss, s, ' ')) {
            command.push_back(s);
        }
        //checks for valid input command
        if (m.find(command.at(0)) == m.end()) {
            cout << "Please enter a valid input." << endl;
            continue;
        }
        //runs relevant method for given input
        switch (m.at(command.at(0))) {
            case mGo:
                cout << goMethod(command, gameMap, newRoom) << endl;
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
                    cout << "Look at what?" << endl;
                    break;
                }
                cout << lookMethod(command, gameMap) << endl;
                break;
            case mKill:
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
        for (int i = 0; i < gameMap.getObjective().getWhat().size(); i++) {
            cout << gameMap.getObjective().getWhat()[i] << endl;
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
}
