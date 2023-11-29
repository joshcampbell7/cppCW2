//
// Created by joshu on 29/11/2023.
//

#include "Objective.h"

Objective::Objective(const string& objectiveId_, const string& roomId_, const vector<string>& what_)
        : objectiveId_(objectiveId_), roomId_(roomId_), what_(what_) {
    // Initialization list is used to initialize member variables
}

std::string Objective::getObjectiveId() const {
    return objectiveId_;
}

std::string Objective::getRoomId() const {
    return roomId_;
}

std::vector<std::string> Objective::getWhat() const {
    return what_;
}
