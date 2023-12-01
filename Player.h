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

    Player(const string &playerId, const string &playerName, const string &currentRoomId);

    string getPlayerId() const;

    string getPlayerName() const;

    string getCurrentRoomId() const;

    int getHealth() const;

    vector<string> getObjects() const;

    void setCurrentRoom(string roomId);

    void setName(string name);

private:
    string playerId;
    string playerName;
    string currentRoomId;
    int health;
    vector<string> objects;


};

#endif //CPPCW2_PLAYER_H