//
// Created by joshu on 29/11/2023.
//

#ifndef CW2_ENEMY_H
#define CW2_ENEMY_H

#include <string>
#include <vector>
#include "Object.h"
#include "Room.h"

using namespace std;

class Enemy {

public:
    Enemy(string enemyId, string description, int aggressiveness, string initialRoom, vector<string> killedBy,
          int health);

    const string &getEnemyName() const;

    const string &getEnemyId() const;

    const string &getDescription() const;

    int getAggressiveness() const;

    const string &getInitialRoom() const;

    const vector<string> &getKilledBy() const;

    int getHealth() const;

    void setHealth(int health);

protected:
    string enemyName_;
    string enemyId_;
    string description_;
    int aggressiveness_;
    string initialRoom_;
    vector<string> killedBy_;
    int health_;
};

#endif //CW2_ENEMY_H
