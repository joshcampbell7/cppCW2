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

//create a map file for use when saving the game
json formatJson(Map &gameMap) {
    json data;
    // Populate the JSON object with sample data
    data["player"]["initialroom"] = gameMap.getPlayer().getCurrentRoom().getRoomId();
    data["player"]["health"] = gameMap.getPlayer().getHealth();

    json objects = json::array(); // Create an array for objects
    for (auto &roomItem: gameMap.getRooms()) {
        for (auto &objectItem: roomItem.second.getObjects()) {
            json object = {
                    {"id",          objectItem.getObjectName()},
                    {"desc",        objectItem.getDescription()},
                    {"initialroom", roomItem.second.getRoomId()}  // Default value
            };
            objects.push_back(object);
        }
    }

    for (auto &playerObject: gameMap.getPlayer().getObjects()) {
        json object = {
                {"id",          playerObject.getObjectName()},
                {"desc",        playerObject.getDescription()},
                {"initialroom", "player"}  // Default value
        };
        objects.push_back(object);
    }
    data["objects"] = objects;


    json enemies = json::array(); // Create an array for rooms
    json roomsArray = json::array();
    for (auto &item: gameMap.getRooms()) {
        json exits = json::object();  // Use json::object() instead of json::array()

        for (const auto &exit: item.second.getExits()) {
            exits[exit.first] = exit.second;
        }
        json roomObject = {
                {"id",    item.second.getRoomId()},
                {"desc",  item.second.getDescription()},
                {"exits", exits},

        };
        roomsArray.push_back(roomObject);
        for (auto &enemyObject: item.second.getEnemies()) {
            json enemy = {
                    {"desc",           enemyObject.getDescription()},
                    {"id",             enemyObject.getEnemyName()},
                    {"aggressiveness", enemyObject.getAggressiveness()},
                    {"initialroom",    item.second.getRoomId()},
                    {"killedby",       enemyObject.getKilledBy()},

            };
            enemies.push_back(enemy);
        }
    }
    data["rooms"] = roomsArray;
    data["enemies"] = enemies;

    json what = json::array();
    for (const auto &item: gameMap.getObjective().getWhat()) {
        what.push_back(item);
    }

    json objectiveArray = {
            {"type", gameMap.getObjective().getType()},
            {"what", what}
    };
    data["objective"] = objectiveArray;
    return data;
}

//read in the map file
Map jsonParser(string jsonFile) {
    try {
        ifstream fin(jsonFile);
        json j;
        fin >> j;

        map<string, Room> rooms;
        map<string, Object> objects;
        map<string, Enemy> enemies;

        //if health is found in the json file, it means it has been saved from earlier so use the saved value rather than the default
        int health = 100;
        if (j["player"].contains("health")) {
            health = j["player"]["health"];
        }

        //initialises rooms with a map of strings for exits
        for (auto &room: j["rooms"]) {
            map<string, string> newMap = room["exits"].get<map<string, string>>();
            Room newRoom = Room(room["id"], room["desc"], newMap);
            //all rooms are added to a map to use in the Map object
            rooms.insert(make_pair(room["id"], newRoom));
        }

        //initialises objects
        int objectId = 1;
        vector<Object> playerObjects;
        for (auto &object: j["objects"]) {
            Object newObject = Object("object" + to_string(objectId), object["id"], object["desc"]);
            //if an object's initialroom is 'player' then it will be added to the player's inventory. otherwise it is added to the room
            if (object["initialroom"] == "player") {
                playerObjects.push_back(newObject);
            } else {
                rooms.at(object["initialroom"]).addObjects(newObject);
            }
            //all rooms are added to a map to use in the Map object
            objects.insert(make_pair("object" + to_string(objectId), newObject));
            objectId++;
        }

        // initialises enemies
        int enemyId = 1;
        for (auto &enemy: j["enemies"]) {
            vector<string> kills = enemy["killedby"].get<vector<string>>();
            Enemy newEnemy = Enemy("enemy" + to_string(enemyId), enemy["id"], enemy["desc"], enemy["aggressiveness"],
                                   kills);
            //add the enemy to the room
            rooms.at(enemy["initialroom"]).addEnemies(newEnemy);
            enemies.insert(make_pair("enemy" + to_string(enemyId), newEnemy));
            enemyId++;
        }

        //initialise the player and add objects in the inventory
        Player player = Player(rooms.at(j["player"]["initialroom"]));
        player.setHealth(health);
        for (Object i: playerObjects) {
            player.addObjects(i);
        }

        //initialise the objective
        Objective objective = Objective("objective1", j["objective"]["type"], j["objective"]["what"]);

        //create a Map object to contain all features in the game's map
        Map gameMap = Map(objects, enemies, rooms, player, objective);
        return gameMap;
    } catch (const exception &e) {
        throw runtime_error("ERROR IN jsonParser.cpp, Failed to parse JSON file: " + string(e.what()));
    }
}
