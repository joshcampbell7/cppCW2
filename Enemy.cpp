//
// Created by joshu on 29/11/2023.
//

#include "Enemy.h"
#include "Object.h"
#include <string>
#include <vector>
using namespace std;

Enemy::Enemy(const string &enemyId, const string &enemyName, const string &description, int aggressiveness,
             const vector<string> &killedBy) : enemyId_(enemyId), enemyName_(enemyName), description_(description),
                                               aggressiveness_(aggressiveness), killedBy_(killedBy) {}


const string &Enemy::getEnemyId() const {
    return enemyId_;
}

const string &Enemy::getEnemyName() const {
    return enemyName_;
}

const string &Enemy::getDescription() const {
    return description_;
}

int Enemy::getAggressiveness() const {
    return aggressiveness_;
}

const vector<string> &Enemy::getKilledBy() const {
    return killedBy_;
}
