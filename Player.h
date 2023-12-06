//
// Created by joshu on 29/11/2023.
//

#ifndef CPPCW2_PLAYER_H
#define CPPCW2_PLAYER_H
#include <string>
#include <vector>
#include "Object.h"
#include "Room.h"

using namespace std;

class Player{
public:

    explicit Player(Room &currentRoom);

    Room& getCurrentRoom();

    int getHealth() const;

    vector<Object> getObjects() const;

    void addObjects(Object &object);

    void setCurrentRoom(Room &currentRoom);

private:
    Room currentRoom;
    int health;
    vector<Object> objects;
};

#endif //CPPCW2_PLAYER_H