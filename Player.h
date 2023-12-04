// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

using namespace std;

class Player {
public:
    Player(const string& playerId, const string& playerName, const string& currentRoomId);

    string getPlayerId() const;
    string getPlayerName() const;
    string getCurrentRoomId() const;
    int getHealth() const;
    vector<string>& getObjects();  // Corrected to return a reference.
    void setCurrentRoom(string roomId);
    void setName(string name);

private:
    string playerId;
    string playerName;
    string currentRoomId;
    int health;
    vector<string> objects;

};

#endif // PLAYER_H
