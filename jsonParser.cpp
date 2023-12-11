/*
 jsonParser.cpp reads the given json file from the user and puts the data into classes
 If there is an error, it will throw an exception
 */

#include "json.hpp"
#include "Objective.h"
#include "Enemy.h"
#include "Room.h"
#include "Object.h"
#include "Player.h"
#include "Map.h"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;
using json = nlohmann::json;

Map jsonParser(string jsonFile) {
    try {
        ifstream fin(jsonFile);
        json j;
        fin >> j;

        map<string, Room> rooms;
        map<string, Object> objects;
        map<string, Enemy> enemies;

        for (auto &room: j["rooms"]) {
            map<string, string> newMap = room["exits"].get<map<string, string>>();
            Room newRoom = Room(room["id"], room["desc"], newMap);
            rooms.insert(make_pair(room["id"], newRoom));
        }

        int objectId = 1;
        for (auto &object: j["objects"]) {
            Object newObject = Object("object" + to_string(objectId), object["id"], object["desc"]);
            rooms.at(object["initialroom"]).addObjects(newObject);
            objects.insert(make_pair("object" + to_string(objectId), newObject));
            objectId++;
        }

        int enemyId = 1;
        for (auto &enemy: j["enemies"]) {
            vector<string> kills = enemy["killedby"].get<vector<string>>();
            Enemy newEnemy = Enemy("enemy" + to_string(enemyId), enemy["id"], enemy["desc"], enemy["aggressiveness"],
                                   kills);
            rooms.at(enemy["initialroom"]).addEnemies(newEnemy);
            enemies.insert(make_pair("enemy" + to_string(enemyId), newEnemy));
            enemyId++;
        }

        Player player = Player(rooms.at(j["player"]["initialroom"]));

        Objective objective = Objective("objective1", j["objective"]["type"], j["objective"]["what"]);

        Map gameMap = Map(objects, enemies, rooms, player, objective);
        return gameMap;
    } catch (const exception &e) {
        throw runtime_error("ERROR IN jsonParser.cpp, Failed to parse JSON file: " + string(e.what()));
    }
}
