//
// Created by joshu on 06/12/2023.
//

#include "Map.h"

Map::Map(map<string, Object> &objects, map<string, Enemy> &enemies, map<string, Room> &rooms, Player &player,
         Objective &objective)
        : objects(objects), enemies(enemies), rooms(rooms), player(player), objective(objective) {}

map<string, Room> &Map::getRooms() {
    return rooms;
}

Player &Map::getPlayer() {
    return player;
}

Objective &Map::getObjective() {
    return objective;
}
