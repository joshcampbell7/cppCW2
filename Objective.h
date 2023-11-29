//
// Created by joshu on 29/11/2023.
//
#include <string>
#include <vector>

using namespace std;

#ifndef CPPCW2_OBJECTIVE_H
#define CPPCW2_OBJECTIVE_H

class Objective{
public:

    Objective(const string &objectiveId_, const string &roomId_, const vector<string> &what_);

    string getObjectiveId() const;
    string getRoomId() const;
    vector<string> getWhat() const;

private:
    string objectiveId_;
    string roomId_;
    vector<string> what_;

};

#endif //CPPCW2_OBJECTIVE_H
