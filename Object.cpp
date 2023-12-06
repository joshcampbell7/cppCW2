//
// Created by joshu on 29/11/2023.
//

#include "Object.h"
#include <string>
using namespace std;

Object::Object(const string &objectId, const string &objectName, const string &description) : objectId_(objectId),
                                                                                              objectName_(objectName),
                                                                                              description_(
                                                                                                      description) {}

const string &Object::getObjectId() const {
    return objectId_;
}

const string &Object::getDescription() const {
    return description_;
}

const string &Object::getObjectName() const {
    return objectName_;
}
