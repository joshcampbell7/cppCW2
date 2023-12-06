//
// Created by joshu on 29/11/2023.
//

#include "Room.h"
#include "Object.h"
#include "Enemy.h"

Room::Room(const string &roomId, const string &description, map<string, string> &exits) : roomId(roomId),
                                                                                                description(
                                                                                                        description),
                                                                                                exits(exits) {}

const string &Room::getRoomId() const {
    return roomId;
}

const string &Room::getDescription() const {
    return description;
}

const map<string, string> &Room::getExits() const {
    return exits;
}

vector<Object> & Room::getObjects() {
    return objects;
}

const vector<Enemy> &Room::getEnemies() const {
    return enemies;
}

void Room::addObjects(Object& object) {
    objects.push_back(object);
}

void Room::addEnemies(Enemy& enemy) {
    enemies.push_back(enemy);
}

void Room::removeObjects(Object &object) {
    for (Object i : objects) {
        if (i==object) {

        }
    }
}

void Room::removeEnemies(Enemy &enemy) {

}
