#include <iostream>
#include <fstream>
#include "Objective.h"
#include "Enemy.h"
#include "json.hpp"
#include <map>
#include "jsonParser.h"
using namespace std;
using json = nlohmann::json;

int main() {
    vector<string> test;
    Objective objective = Objective("testId","This is a test description",test);
    std::cout << objective.getRoomId() << objective.getObjectiveId() << std::endl;

    jsonParser();

    return 0;
}
