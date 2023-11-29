//
// Created by joshu on 29/11/2023.
//

#include "Enemy.h"
#include "Object.h"
#include "Room.h"
#include <string>
#include <vector>
using namespace std;

Enemy::Enemy(string enemyId, string description, int aggressiveness, string initialRoom, vector<string> killedBy, int health) {
    enemyId_ = enemyId;
    description_ = description;
    aggressiveness_ = aggressiveness;
    initialRoom_ = initialRoom;
    killedBy_ = killedBy;
    health_ = health;
}


int Enemy::getHealth() const {
    return health_;
}

void Enemy::setHealth(int health) {
    health_ = health;
}

const string &Enemy::getEnemyName() const {
    return enemyName_;
}

const string &Enemy::getEnemyId() const {
    return enemyId_;
}

const string &Enemy::getDescription() const {
    return description_;
}

int Enemy::getAggressiveness() const {
    return aggressiveness_;
}

const string &Enemy::getInitialRoom() const {
    return initialRoom_;
}

const vector<string> &Enemy::getKilledBy() const {
    return killedBy_;
}

