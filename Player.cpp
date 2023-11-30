//
// Created by joshu on 30/11/2023.
//

#include "Player.h"

Player::Player(const string &playerId, const string &playerName, const string &initialRoomId) : playerId(playerId), playerName(playerName),
                                                initialRoomId(initialRoomId), health(100), objects({}) {}

string Player::getPlayerId() const {
    return playerId;
}

string Player::getPlayerName() const {
    return playerName;
}

string Player::getInitialRoomId() const {
    return initialRoomId;
}

int Player::getHealth() const {
    return health;
}

vector<string> Player::getObjects() const {
    return objects;
}

