//
// Created by joshu on 29/11/2023.
//

#ifndef CPPCW2_OBJECTIVE_H
#define CPPCW2_OBJECTIVE_H

#include <string>
#include <vector>

using namespace std;

class Objective {
public:

    Objective(const string &objectiveId_, const string &type_, const vector<string> &what_);

    string getObjectiveId() const;

    string getType() const;

    vector<string> getWhat() const;

    void removeWhat(string &what);

private:
    string objectiveId_;
    string type_;
    vector<string> what_;
};

#endif //CPPCW2_OBJECTIVE_H
