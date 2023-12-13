//
// Created by joshu on 30/11/2023.
//

#ifndef CPPCW2_MAINENGINE_H
#define CPPCW2_MAINENGINE_H

#endif //CPPCW2_MAINENGINE_H

#include <vector>
#include "Player.h"
#include "Map.h"

using namespace std;

string goMethod(const vector<string> &command, Map &gameMap);

string takeMethod(const vector<string> &command, Map &gameMap);

string lookMethod(const vector<string> &command, Map &gameMap);

string killMethod(const vector<string> &command, Map &gameMap);

string saveMethod(const vector<string> &command, Map &gameMap);

void moveHandler(Map &gameMap);

void mainEngine(Map &gameMap);
