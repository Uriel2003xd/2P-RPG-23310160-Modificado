//
// Created by Victor Navarro on 19/02/24.
//

#ifndef RPG_COMBAT_H
#define RPG_COMBAT_H

#include <vector>
#include <queue>
#include <string>
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "Action.h"

class Combat {
private:
    std::vector<Character*> participants;
    std::vector<Player*> partyMembers;
    std::vector<Character*> originalMembers;
    std::vector<Enemy*> enemies;
    std::priority_queue<Action> actionQueue;

    void registerActions(std::vector<Character*>::iterator participant);
    void executeActions(std::vector<Character*>::iterator participant);
    void checkParticipantStatus(Character* participant);
    void combatPrep();
    Character* getTarget(Character* attacker);

public:
    Combat(std::vector<Character*> _participants);
    Combat(std::vector<Player*> _partyMembers, std::vector<Enemy*> _enemies);
    Combat();

    void heal();
    void doCombat();
    void addParticipant(Character* participant);
    std::string toString() const;
    std::vector<Character*> getOriginalMembers() const;
};

#endif // RPG_COMBAT_H

