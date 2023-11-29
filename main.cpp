#include <iostream>
#include "Room.h"
#include "Object.h"
#include "Enemy.h"
#include <vector>
#include <map>
using namespace std;

int main() {
    vector<string> x;
    Object table("table1","made of wood", "room1",0);
    Enemy zombie("enemy1", "will kill you", 100, "room1", x, 50);
    cout << table.getDescription() << endl;
    cout << zombie.getDescription() << endl;
    return 0;
}
