//
// Created by joshu on 30/11/2023.
//

#include "Player.h"
#include "Object.h"
#include "Room.h"
#include <algorithm>

Player::Player(Room &currentRoom) : currentRoom(currentRoom), health(100), objects() {}

Room& Player::getCurrentRoom() {
    return currentRoom;
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int newHealth){
    health = newHealth;
}

vector<Object> Player::getObjects() const {
    return objects;
}

void Player::setCurrentRoom(Room &newCurrentRoom) {
    Player::currentRoom = newCurrentRoom;
}

void Player::addObjects(Object &object) {
    objects.push_back(object);
}

void Player::removeObject(Object &object) {
    auto it = find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

