//
// Created by joshu on 29/11/2023.
//
#include <string>
#include <vector>

using namespace std;
#ifndef CPPCW2_PLAYER_H
#define CPPCW2_PLAYER_H

class Player{
public:
    Player(const string &playerId, const string &playerName, const string &initialRoomId, int health,
           const vector<string> &objects) : playerId(playerId), playerName(playerName), initialRoomId(initialRoomId),
                                            health(health), objects(objects) {}

    const string &getPlayerId() const {
        return playerId;
    }

    const string &getPlayerName() const {
        return playerName;
    }

    const string &getInitialRoomId() const {
        return initialRoomId;
    }

    int getHealth() const {
        return health;
    }

    const vector<string> &getObjects() const {
        return objects;
    }

private:
    string playerId;
    string playerName;
    string initialRoomId;
    int health = 100;
    vector<string> objects;


};

#endif //CPPCW2_PLAYER_H
