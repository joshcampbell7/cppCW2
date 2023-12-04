//
// Created by joshu on 29/11/2023.
//
#include <string>
#include <vector>
#include <map>

using namespace std;
#ifndef CPPCW2_ROOM_H
#define CPPCW2_ROOM_H

class Room{
public:
    Room(const string &roomId, const string &description, const map<string, string> &exits, vector<string> &objects);

    const string &getRoomId() const;

    const string &getDescription() const;

    const map<string, string> &getExits() const;

    vector<string> &getObjects();

private:
    string roomId;
    string description;
    map<string,string> exits;
    vector<string> objects;
};

#endif //CPPCW2_ROOM_H
