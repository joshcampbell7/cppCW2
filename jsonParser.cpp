//
// Created by joshu on 30/11/2023.
//

#include <iostream>
#include <fstream>
#include "Objective.h"
#include "Enemy.h"
#include "json.hpp"
#include <map>
using namespace std;
using json = nlohmann::json;

void jsonParser() {
    try {
        ifstream fin("C:\\Users\\joshu\\OneDrive\\Documents\\University\\3rd year coding\\C++\\CW2\\map1.json");
        json j;
        fin >> j; // read from file into j
        cout << j["enemies"];

// This outputs how many things there are at the top level
// and the keys (5: rooms, objects, enemies, player, objective)
        int numTypes = j.size();
        cout << numTypes << endl;

        for (auto e: j.items()) {
            string s = e.key();
            cout << s << endl;
        }

        for (const auto &enemy: j["enemies"]) {
            Enemy enemy1 = Enemy("Zombie", "enemy1", enemy["desc"], enemy["aggressiveness"], enemy["initialroom"],
                                 enemy["killedby"], 100);
            cout << enemy1.getInitialRoom();
        }


    } catch (exception e) {
        cout << "fail";
    }
}