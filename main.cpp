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

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            throw invalid_argument("Usage: " + string(argv[0]) + " <json_file_path>");
        }
        string jsonFile = argv[1];
        Map gameMap = jsonParser(jsonFile);
        mainEngine(gameMap);
        return 0;
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
}
