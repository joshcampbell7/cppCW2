#include <iostream>
#include <fstream>
#include "Objective.h"
#include "Enemy.h"
#include "json.hpp"
#include "jsonParser.h"
#include "mainEngine.h"
using namespace std;
using json = nlohmann::json;

int main() {
    jsonParser();
    mainEngine();
    return 0;
}
