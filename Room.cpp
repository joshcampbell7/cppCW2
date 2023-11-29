//
// Created by joshu on 29/11/2023.
//

#include "Room.h"

Room::Room(const string &roomId, const string &description, const map<string, string> &exits) : roomId(roomId),
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
