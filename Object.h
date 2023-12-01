//
// Created by joshu on 29/11/2023.
//

#ifndef CW2_OBJECT_H
#define CW2_OBJECT_H

#include <string>
#include "Room.h"
using namespace std;

class Object {

public:
    Object(string objectId, string description, string initialRoom, int damage,string objectName);

    const string &getObjectName() const;

    const string &getObjectId() const;

    const string &getDescription() const;

    const string &getInitialRoom() const;

    int getDamage() const;

protected:
    string objectName_;
    string objectId_;
    string description_;
    string initialRoom_;
    int damage_;
};

#endif //CW2_OBJECT_H
