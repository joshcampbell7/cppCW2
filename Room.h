//
// Created by joshu on 29/11/2023.
//
#include <string>
#include <vector>
#include <map>

using namespace std;
#ifndef CPPCW2_ROOM_H
#define CPPCW2_ROOM_H

class Room {
public:
    Room(const string &roomId, const string &description, const map<string, string> &exits,
         const vector<string> &objects, const vector<string> &enemies);

    const string &getRoomId() const;

    const string &getDescription() const;

    const map<string, string> &getExits() const;

    const vector<string> &getObjects() const;

    const  vector<string> &getEnemies() const;

private:
    string roomId;
    string description;
    map<string, string> exits;
    vector<string> objects;
    vector<string> enemies;
};

#endif //CPPCW2_ROOM_H
