//
// Created by joshu on 29/11/2023.
//

#ifndef CPPCW2_ROOM_H
#define CPPCW2_ROOM_H

#include <string>
#include <vector>
#include <map>
#include "Enemy.h"
#include "Object.h"

using namespace std;

class Room {
public:
    Room() = default;

    Room(const string &roomId, const string &description, map<string, string> &exits);

    const string &getRoomId() const;

    const string &getDescription() const;

    const map<string, string> &getExits() const;

    vector<Object> &getObjects();

    vector<Enemy> &getEnemies();

    void addObjects(Object &object);

    void addEnemies(Enemy &enemy);

    void removeObjects(Object &object);

    void removeEnemies(Enemy &enemy);

private:
    string roomId;
    string description;
    map<string, string> exits;
    vector<Object> objects;
    vector<Enemy> enemies;
};

#endif //CPPCW2_ROOM_H
