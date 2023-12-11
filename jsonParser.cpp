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

json formatJson(Map &gameMap){
    json data;
    // Populate the JSON object with sample data
    data["player"]["initialroom"] = gameMap.getPlayer().getCurrentRoom().getRoomId();
    data["player"]["health"] = gameMap.getPlayer().getHealth();

    json objects = json::array(); // Create an array for objects
    for (auto& roomItem : gameMap.getRooms()) {
        for (auto& objectItem : roomItem.second.getObjects()) {
            json object = {
                    {"id", objectItem.getObjectName()},
                    {"desc", objectItem.getDescription()},
                    {"initialroom", roomItem.second.getRoomId()}  // Default value
            };
            objects.push_back(object);
            cout<<"length of player inventory is: " << gameMap.getPlayer().getObjects().size() <<endl;
        }
    }

    for (auto& playerObject : gameMap.getPlayer().getObjects()) {
        json object = {
                {"id", playerObject.getObjectName()},
                {"desc", playerObject.getDescription()},
                {"initialroom", "player"}  // Default value
        };
        objects.push_back(object);
    }
    data["objects"] = objects;


    json enemies = json::array(); // Create an array for rooms
    for (const auto& item : gameMap.getEnemies()) {
        json enemy = {
                {"enemyName", item.second.getEnemyName()},
                {"enemyDescription", item.second.getDescription()},
                {"enemyId", item.second.getEnemyId()},
                {"aggressiveness", item.second.getAggressiveness()}
        };

        enemies.push_back(enemy);
    }
    data["enemies"] = enemies;

    json roomsArray = json::array();
    for (auto& item : gameMap.getRooms()) {
        json exits = json::array();
        exits.push_back(item.second.getExits());
        json roomObject = {
                {"roomId", item.second.getRoomId()},
                {"roomDescription", item.second.getDescription()},
                {"exits", exits},

        };

        roomsArray.push_back(roomObject);
    }
    data["rooms"] = roomsArray;


    json what = json::array();
    for (const auto& item : gameMap.getObjective().getWhat()) {
        what.push_back(item);
    }

    json objectiveArray = {
            {"objectiveType",gameMap.getObjective().getType()},
            {"what",what}
    };
    data["objective"] = objectiveArray;
    return data;
}

Map jsonParser(string jsonFile) {
    try {
        ifstream fin(jsonFile);
        json j;
        fin >> j;

        map<string, Room> rooms;
        map<string, Object> objects;
        map<string, Enemy> enemies;

        int health = 100;
        if(j["player"].contains("health")){
            health = j["player"]["health"];
        }

        for (auto &room: j["rooms"]) {
            map<string, string> newMap = room["exits"].get<map<string, string>>();
            Room newRoom = Room(room["id"], room["desc"], newMap);
            rooms.insert(make_pair(room["id"], newRoom));
        }

        int objectId = 1;
        vector<Object> playerObjects;
        for (auto &object: j["objects"]) {
            Object newObject = Object("object" + to_string(objectId), object["id"], object["desc"]);
            if (object["initialroom"] == "player") {
                playerObjects.push_back(newObject);
            } else {
                rooms.at(object["initialroom"]).addObjects(newObject);
            }
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
        player.setHealth(health);
        for (Object i : playerObjects) {
            player.addObjects(i);
        }

        Objective objective = Objective("objective1", j["objective"]["type"], j["objective"]["what"]);

        Map gameMap = Map(objects, enemies, rooms, player, objective);
        return gameMap;
    } catch (const exception &e) {
        throw runtime_error("ERROR IN jsonParser.cpp, Failed to parse JSON file: " + string(e.what()));
    }
}
