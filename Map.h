//
// Created by joshu on 06/12/2023.
//

#ifndef CPPCW2_MAP_H
#define CPPCW2_MAP_H

#include <map>
#include <string>
#include "Object.h"
#include "Enemy.h"
#include "Room.h"
#include "Player.h"
#include "Objective.h"

using namespace std;

class Map {

public:
    Map(map<string, Object> &objects, map<string, Enemy> &enemies, map<string, Room> &rooms, Player &player,
        Objective &objective);

    map<string, Room> &getRooms();

    Player &getPlayer();

    Objective &getObjective();

private:
    map<string, Object> objects;
    map<string, Enemy> enemies;
    map<string, Room> rooms;
    Player player;
    Objective objective;
};

#endif //CPPCW2_MAP_H
