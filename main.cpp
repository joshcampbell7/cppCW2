#include <iostream>
#include <fstream>
#include "Objective.h"
#include "Enemy.h"
#include "json.hpp"
#include "jsonParser.h"
#include "mainEngine.h"
#include "Map.h"

using namespace std;
using json = nlohmann::json;

int main() {
    string jsonFile = "../map1.json";
    Map gameMap = jsonParser(jsonFile);
    mainEngine(gameMap);
    return 0;
}
