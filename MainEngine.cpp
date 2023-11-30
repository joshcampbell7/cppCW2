//
// Created by joshu on 30/11/2023.
//

#include <iostream>
#include "MainEngine.h"
#include "Player.h"
#include "jsonParser.h"
using namespace std;
void mainEngine(){
    cout << "Welcome to Map .. of Text Adventure Game" << endl;
    cout << "Before we start, What is your name?" << endl;
    string name;
    cin >> name;
    Player player = Player("123TestId",name,"this is initial room");

    cout << "Welcome " + player.getPlayerName() + "!, " + "you have " + to_string(player.getHealth()) + " health to start with. " + "You also have " + to_string(player.getObjects().size()) + " objects in your inventory." << endl;

    if(getObjectives().at("objective1").getType() == "kill"){
        cout << "To win the game, your objective is to Kill the following: " << endl;
        for(int i=0;i<getObjectives().at("objective1").getWhat().size();i++){
            cout << getObjectives().at("objective1").getWhat().at(i) << endl;
        }
    }

    if(getObjectives().at("objective1").getType() == "collect"){
        cout << "To win the game, your objective is to collect the following items: " << endl;
        for(int i=0;i<getObjectives().at("objective1").getWhat().size();i++){
            cout << getObjectives().at("objective1").getWhat().at(i) << endl;
        }
    }

    //Add code to handle other objects

    //call method that handles the user inputs etc

}