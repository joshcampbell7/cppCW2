//
// Created by joshu on 06/12/2023.
//

#include "Map.h"

Map::Map(map<string, Object> &objects, map<string, Enemy> &enemies, map<string, Room> &rooms, Player &player, Objective &objective)
        : objects(objects), enemies(enemies), rooms(rooms), player(player), objective(objective) {}

map<string, Enemy> &Map::getEnemies() {
    return enemies;
}

map<string, Room> &Map::getRooms() {
    return rooms;
}

map<string, Object> &Map::getObjects() {
    return objects;
}

Player& Map::getPlayer() {
    return player;
}

Objective &Map::getObjective() {
    return objective;
}

void Map::setObjects(map<string, Object> &objectsRep) {
    Map::objects = objectsRep;
}

void Map::setEnemies(map<string, Enemy> &enemiesRep) {
    Map::enemies = enemiesRep;
}

void Map::setRooms(map<string, Room> &roomsRep) {
    Map::rooms = roomsRep;
}
