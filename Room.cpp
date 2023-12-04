//
// Created by joshu on 29/11/2023.
//

#include "Room.h"

Room::Room(const string &roomId, const string &description, const map<string, string> &exits, vector<string> &objects) : roomId(roomId),
                                                                                                description(
                                                                                                        description),
                                                                                                exits(exits),
                                                                                                objects(objects) {}

const string &Room::getRoomId() const {
    return roomId;
}

const string &Room::getDescription() const {
    return description;
}

const map<string, string> &Room::getExits() const {
    return exits;
}

vector<string> &Room::getObjects()  {
    return objects;
}