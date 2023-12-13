//
// Created by joshu on 29/11/2023.
//

#include <algorithm>
#include "Objective.h"

Objective::Objective(const string &objectiveId_, const string &type_, const vector<string> &what_)
        : objectiveId_(objectiveId_), type_(type_), what_(what_) {
    // Initialization list is used to initialize member variables
}

std::string Objective::getObjectiveId() const {
    return objectiveId_;
}

std::string Objective::getType() const {
    return type_;
}

std::vector<std::string> Objective::getWhat() const {
    return what_;
}

//finds the given object/room/enemy form the what_ list and removes it
void Objective::removeWhat(string &what) {
    auto it = find(what_.begin(), what_.end(), what);
    if (it != what_.end()) {
        what_.erase(it);
    }
}
