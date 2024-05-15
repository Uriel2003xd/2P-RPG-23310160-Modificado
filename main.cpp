#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"

int main() {
    Player *player = new Player("Predeterminado", 100, 20, 5, 10);

    player->unserialize("Guardado.txt");
    Enemy *enemy = new Enemy("Carmencita", 10, 15, 4, 20, 100);
    Enemy *enemy2 = new Enemy("Blanquita", 10, 30, 4, 5, 100);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;
    return 0;
}
