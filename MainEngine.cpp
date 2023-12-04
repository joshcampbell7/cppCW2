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

using namespace std;

string goMethod(const vector<string> &command, Player &player, bool &newRoom) {
    if (getRooms().at(player.getCurrentRoomId()).getExits().count(command.at(1))) {
        player.setCurrentRoom(getRooms().at(player.getCurrentRoomId()).getExits().at(command.at(1)));
        newRoom = true;
        return "Travelling " + command.at(1) + "...";
    }
    newRoom = false;
    return "Please enter a valid direction.";
}

string takeMethod(const vector<string> &command, Player &player) {
    return "This is the take method.";
}

string lookMethod(const vector<string> &command, Player &player) {
    vector<string> objectsInRoom = getRooms().at(player.getCurrentRoomId()).getObjects();
    for (auto &objectName: objectsInRoom) {
        Object object = getObjects().at(objectName);
        if (command.at(1) == object.getObjectName()) {
            return object.getDescription() + " Be sure to take it first though...";
        }
    }
    return "That object is not in this room...";
}

string fightMethod(const vector<string> &command, Player &player) {
    return "This is the fight method.";
}

string moveHandler(Player &player) {
    //enum and map set up to facilitate use of switch case statements as they can't handle strings
    enum moveCode {
        mGo, mTake, mLook, mFight
    };
    map<string, moveCode> m = {{"look",  mLook},
                               {"go",    mGo},
                               {"take",  mTake},
                               {"fight", mFight}};

    cout << "\nYou have 4 input command options: go, look, take, fight." << endl;
    bool newRoom = true;
    while (!getObjectives().at("objective1").getWhat().empty()) {
        if (newRoom) {
            cout << "\nYou are currently in " + player.getCurrentRoomId() + ". " +
                    getRooms().at(player.getCurrentRoomId()).getDescription() << endl;
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
                cout << goMethod(command, player, newRoom) << endl;
                break;
            case mTake:
                cout << takeMethod(command, player) << endl;
                break;
            case mLook:
                if (command.size() < 2) {
                    cout << "Look at what?" << endl;
                    break;
                }
                cout << lookMethod(command, player) << endl;
                break;
            case mFight:
                cout << fightMethod(command, player) << endl;
                break;
            default:
                cout << "Please enter a valid input." << endl;
                break;
        }
    }
    return "";
}

void mainEngine() {
    cout << "Welcome to Map .. of Text Adventure Game" << endl;
    cout << "Before we start, What is your name?" << endl;
    string name;
    cin >> name;
    Player player = Player("testId", name, getInitialRoom());

    cout << "Welcome " + player.getPlayerName() + "!, " + "you have " + to_string(player.getHealth()) +
            " health to start with. " + "You also have " + to_string(player.getObjects().size()) +
            " objects in your inventory." << endl;

    if (getObjectives().at("objective1").getType() == "kill") {
        cout << "\nTo win the game, your objective is to kill the following enemies: " << endl;
        for (int i = 0; i < getObjectives().at("objective1").getWhat().size(); i++) {
            cout << getObjectives().at("objective1").getWhat().at(i) << endl;
        }
    }

    if (getObjectives().at("objective1").getType() == "collect") {
        cout << "\nTo win the game, your objective is to collect the following items: " << endl;
        for (string i: getObjectives().at("objective1").getWhat()) {
            cout << i << endl;
        }
    }

    if (getObjectives().at("objective1").getType() == "room") {
        cout << "\nTo win the game, your objective is to visit the following rooms: " << endl;
        for (string i: getObjectives().at("objective1").getWhat()) {
            cout << i << endl;
        }
    }

    //Add code to handle other objects

    //call method that handles the user inputs etc
    moveHandler(player);
}
