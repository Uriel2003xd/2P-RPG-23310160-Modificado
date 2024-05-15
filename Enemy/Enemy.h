//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H

#include "../Character/Character.h"
#include "../Player/Player.h"
#include <vector>
#include "../Combat/Action.h"

class Player;

class Enemy : public Character {
private:
    int experience;
public:
    Enemy(char* _name, int _health, int _attack, int _defense, int _speed, int _experience);
    void doAttack(Character* target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(std::vector<Player*> possibleTargets);
    Action takeAction(std::vector<Player*> partyMembers);
    int getExperience();
    void moreDificult();
};

#endif // RPG_ENEMY_H

