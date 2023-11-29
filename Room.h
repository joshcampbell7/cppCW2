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
    Room(const string &roomId, const string &description, const map<string, string> &exits);

    const string &getRoomId() const;

    const string &getDescription() const;

    const map<string, string> &getExits() const;


private:
    string roomId;
    string description;
    map<string,string> exits;
};

#endif //CPPCW2_ROOM_H
