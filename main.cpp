#include <iostream>
#include "Objective.h"

int main() {
    vector<string> test;
    Objective objective = Objective("testId","This is a test description",test);
    std::cout << objective.getRoomId() << objective.getObjectiveId() << std::endl;
    return 0;
}
