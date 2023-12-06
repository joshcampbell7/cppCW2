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

    const string &getObjectId() const;

    const string &getObjectName() const;

    const string &getDescription() const;

    bool operator==(const Object& other) const {
        return this->objectId_ == other.objectId_;
    }

private:
    string objectId_;
    string objectName_;
    string description_;
};

#endif //CW2_OBJECT_H
