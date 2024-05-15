//
// Created by Victor Navarro on 19/02/24.
//

#include "Combat.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Function to compare the speed of two characters
bool compareSpeed(Character* a, Character* b) {
    return a->getSpeed() > b->getSpeed();
}

// Constructor with participants
Combat::Combat(vector<Character*> _participants) {
    participants = std::move(_participants);
    originalMembers = participants;

    for (auto participant : participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back(static_cast<Player*>(participant));
        } else {
            enemies.push_back(static_cast<Enemy*>(participant));
        }
    }
}

// Constructor with party members and enemies
Combat::Combat(vector<Player*> _partyMembers, vector<Enemy*> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
    participants.reserve(partyMembers.size() + enemies.size());
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());
    participants.insert(participants.end(), enemies.begin(), enemies.end());
}

// Default constructor
Combat::Combat() : participants(), partyMembers(), enemies() {}

// Add a participant to the combat
void Combat::addParticipant(Character* participant) {
    participants.push_back(participant);
    if (participant->getIsPlayer()) {
        partyMembers.push_back(static_cast<Player*>(participant));
    } else {
        enemies.push_back(static_cast<Enemy*>(participant));
    }
}

// Prepare for combat by sorting participants by speed
void Combat::combatPrep() {
    sort(participants.begin(), participants.end(), compareSpeed);
}

// Convert combat state to string
string Combat::toString() const {
    string result;
    for (auto participant : participants) {
        result += participant->toString() + "\n";
    }
    cout << "====================" << endl;
    return result;
}

// Get a target for the attacker
Character* Combat::getTarget(Character* attacker) {
    for (auto participant : participants) {
        if (participant->getIsPlayer() != attacker->getIsPlayer()) {
            return participant;
        }
    }
    // Handle this exception appropriately
    return nullptr;
}

// Main combat loop
void Combat::doCombat() {
    bool combat = true;
    while (combat) {
        cout << "Se ha iniciado el combate" << endl;
        combatPrep();
        int round = 1;

        while (!enemies.empty() && !partyMembers.empty()) {
            cout << "\nRonda " << round << endl;
            auto it = participants.begin();
            registerActions(it);
            executeActions(it);
            round++;
        }

        if (enemies.empty()) {
            cout << "Felicidades has ganado" << endl;
        } else {
            cout << "Has Perdido" << endl;
        }

        cout << "Quieres Jugar De Nuevo? (1.Si/2.No)" << endl;
        char playAgain;
        cin >> playAgain;

        if (playAgain == '2') {
            for (auto player : partyMembers) {
                player->serialize("Guardado.txt");
            }
            combat = false;
        } else {
            participants.clear();
            partyMembers.clear();
            enemies.clear();

            for (auto participant : originalMembers) {
                addParticipant(participant);
            }

            heal();

            cout << "Quieres incrementar el nivel de dificultad? (1.Si/2.No)" << endl;
            char increaseDifficulty;
            cin >> increaseDifficulty;

            if (increaseDifficulty == '1') {
                for (auto enemy : enemies) {
                        enemy->moreDificult();
                }
            }
        }
    }
}

// Execute the actions in the action queue
void Combat::executeActions(vector<Character*>::iterator participant) {
    while (!actionQueue.empty()) {
        Action currentAction = actionQueue.top();
        currentAction.action();
        actionQueue.pop();

        checkParticipantStatus(*participant);
        checkParticipantStatus(currentAction.target);
    }
}

// Check the status of a participant
void Combat::checkParticipantStatus(Character* participant) {
    if (participant->getHealth() <= 0) {
        if (participant->getIsPlayer()) {
            partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), participant), partyMembers.end());
        } else {
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

// Register actions for each participant
void Combat::registerActions(vector<Character*>::iterator participantIterator) {
    while (participantIterator != participants.end()) {
        if ((*participantIterator)->getIsPlayer()) {
            Action playerAction = static_cast<Player*>(*participantIterator)->takeAction(enemies);
            actionQueue.push(playerAction);
        } else {
            Action enemyAction = static_cast<Enemy*>(*participantIterator)->takeAction(partyMembers);
            actionQueue.push(enemyAction);
        }
        participantIterator++;
    }
}

// Get the original members of the combat
vector<Character*> Combat::getOriginalMembers() const {
    return originalMembers;
}

// Heal all participants to their original health
void Combat::heal() {
    for (auto participant : participants) {
        participant->heal();
    }
}
