//
// Created by joshu on 30/11/2023.
//

#include "Player.h"

Player::Player(const string &playerId, const string &playerName, const string &currentRoomId) : playerId(playerId), playerName(playerName),
                                                currentRoomId(currentRoomId), health(100), objects({}) {}

string Player::getPlayerId() const {
    return playerId;
}

string Player::getPlayerName() const {
    return playerName;
}

string Player::getCurrentRoomId() const {
    return currentRoomId;
}

int Player::getHealth() const {
    return health;
}

vector<string> Player::getObjects() const {
    return objects;
}

void Player::setCurrentRoom(string roomId) {
    currentRoomId = roomId;
}

void Player::setName(string name){
    playerName = name;
}
