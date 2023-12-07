//
// Created by joshu on 29/11/2023.
//

#include <algorithm>
#include "Room.h"
#include "Object.h"
#include "Enemy.h"
using namespace std;

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

vector<Enemy> & Room::getEnemies(){
    return enemies;
}

void Room::addObjects(Object& object) {
    objects.push_back(object);
}

void Room::addEnemies(Enemy& enemy) {
    enemies.push_back(enemy);
}

void Room::removeObjects(Object &object) {
    auto it = find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

void Room::removeEnemies(Enemy &enemy) {
    auto it = find(enemies.begin(), enemies.end(), enemy);
    if (it != enemy.end()) {
        enemy.erase(it);
    }

}

void Room::setObjects(const vector<Object> &newObjects) {
    Room::objects = objects;
}
