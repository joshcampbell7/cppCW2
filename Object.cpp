//
// Created by joshu on 29/11/2023.
//

#include "Object.h"
#include "Room.h"
#include <string>

using namespace std;

Object::Object(string objectId, string description, string initialRoom, int damage, string objectName) {
    objectId_ = objectId;
    description_ = description;
    initialRoom_ = initialRoom;
    damage_ = damage;
    objectName_ = objectName;
}

const string &Object::getObjectName() const {
    return objectName_;
}

const string &Object::getObjectId() const {
    return objectId_;
}

const string &Object::getDescription() const {
    return description_;
}

const string &Object::getInitialRoom() const {
    return initialRoom_;
}

int Object::getDamage() const {
    return damage_;
}
