#include <iostream>
#include <fstream>
#include "Objective.h"
#include "json.hpp"
#include "jsonParser.h"
#include "MainEngine.h"
#include "Map.h"

using namespace std;
using json = nlohmann::json;

//program takes 2 arguments: ./main and map name
int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            throw invalid_argument("Usage: " + string(argv[0]) + " <json_file_path>");
        }
        string jsonFile = argv[1];
        //load in map
        Map gameMap = jsonParser(jsonFile);
        //play game
        mainEngine(gameMap);
        return 0;
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
}
