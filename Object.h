//
// Created by joshu on 29/11/2023.
//

#ifndef CW2_OBJECT_H
#define CW2_OBJECT_H

#include <string>

using namespace std;

class Object {

public:
    Object(const string &objectId, const string &objectName, const string &description);

    const string &getObjectName() const;

    const string &getDescription() const;

    //redefinition of the == operator to allow the find function to be used in the Room class when removing objects
    bool operator==(const Object &other) const {
        return this->objectId_ == other.objectId_;
    }

private:
    string objectId_;
    string objectName_;
    string description_;
};

#endif //CW2_OBJECT_H
