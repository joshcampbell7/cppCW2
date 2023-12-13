//
// Created by joshu on 30/11/2023.
//

#ifndef CPPCW2_JSONPARSER_H
#define CPPCW2_JSONPARSER_H

#include <map>
#include "Objective.h"
#include "Enemy.h"
#include "Room.h"
#include "Object.h"
#include "Player.h"
#include "Map.h"
#include "json.hpp"

using json = nlohmann::json;
#endif //CPPCW2_JSONPARSER_H

Map jsonParser(string jsonFile);

json formatJson(Map &gameMap);
