//
// Created by joshu on 29/11/2023.
//

#include "Room.h"

Room::Room(const string &roomId, const string &description, const map <string, string> &exits,
           const vector<string> &objects, const vector<string> &enemies) : roomId(roomId),
                                                                                       description(
                                                                                               description),
                                                                                       exits(exits),
                                                                                       objects(objects),
                                                                                       enemies(enemies) {}

const string &Room::getRoomId() const {
    return roomId;
}

const string &Room::getDescription() const {
    return description;
}

const map <string, string> &Room::getExits() const {
    return exits;
}

const vector<string> &Room::getObjects() const {
    return objects;
}

const vector<string> &Room::getEnemies() const {
    return enemies;
}
