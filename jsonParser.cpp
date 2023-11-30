//
// Created by joshu on 30/11/2023.
//

#include "json.hpp"
#include "Objective.h"
#include "Enemy.h"
#include "Room.h"
#include "Object.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;
using json = nlohmann::json;

map<string,Enemy> Enemies;
map<string,Room> Rooms;
map<string,Object> Objects;
map<string,Objective> Objectives;
string initialroom;

void jsonParser() {
    try {
        ifstream fin("../map1.json");
        json j;
        fin >> j; // read from file into j

// This outputs how many things there are at the top level
// and the keys (5: rooms, objects, enemies, player, objective)
        int numTypes = j.size();
        for (auto e: j.items()) {
            string s = e.key();
        }
        map<string,any> allObjects;
        int enemyId=1;
        for (const auto &enemy: j["enemies"]) {
            Enemy enemy1 = Enemy("Zombie", "enemy"+to_string(enemyId), enemy["desc"], enemy["aggressiveness"], enemy["initialroom"],
                                 enemy["killedby"], 100);
            Enemies.insert({enemy1.getEnemyId(),enemy1});
            enemyId++;
        }
        for (const auto &room: j["rooms"]) {
            Room room1 = Room(room["id"], room["desc"],room["exits"]);
            Rooms.insert({room1.getRoomId(),room1});
        }
        int objectId=1;
        for (const auto &object: j["objects"]) {
            Object object1 = Object("object"+to_string(objectId), object["desc"],object["initialroom"],0);
            Objects.insert({object1.getObjectId(),object1});
            objectId++;
        }
        Objective objective1 = Objective("objective1",j["objective"]["type"],j["objective"]["what"]);
        Objectives.insert({objective1.getObjectiveId(),objective1});
        initialroom= j["player"]["initialroom"];


    } catch (exception e) {
        cout << "fail";
    }
}

map<string,Object> getObjects(){
    return Objects;
}
map<string,Room> getRooms(){
    return Rooms;
}
map<string,Enemy> getEnemies(){
    return Enemies;
}
map<string,Objective> getObjectives(){
    return Objectives;
}
string getInitialRoom(){
    return initialroom;
}
