//
// Created by joshu on 29/11/2023.
//

#ifndef CW2_ENEMY_H
#define CW2_ENEMY_H

#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Enemy {

public:
    Enemy(const string &enemyId, const string &enemyName, const string &description, int aggressiveness,
          const vector<string> &killedBy);

    const string &getEnemyId() const;

    const string &getEnemyName() const;

    const string &getDescription() const;

    int getAggressiveness() const;

    const vector<string> &getKilledBy() const;

private:
    string enemyId_;
    string enemyName_;
    string description_;
    int aggressiveness_;
    vector<string> killedBy_;
};

#endif //CW2_ENEMY_H
