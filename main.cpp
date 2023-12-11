#include <iostream>
#include <fstream>
#include "Objective.h"
#include "Enemy.h"
#include "json.hpp"
#include "jsonParser.h"
#include "MainEngine.h"
#include "Map.h"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <json_file_path>" << endl;
        return 1;
    }

    string jsonFile = argv[1];
    cout << "Attempting to open JSON file: " << jsonFile << endl;

    // Create an instance of Map using the specified JSON file
    Map gameMap = jsonParser(jsonFile);

    // Call your mainEngine function with the created Map instance
    mainEngine(gameMap);

    return 0;
}
