//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
#include <cstdlib>

Character::Character(const std::string& _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer)
        : name(_name), health(_health), originalHealth(_health), attack(_attack), defense(_defense), speed(_speed), isPlayer(_isPlayer) {}

const std::string& Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

int Character::getOriginalHealth() const {
    return originalHealth;
}

int Character::getAttack() const {
    return attack;
}

int Character::getDefense() const {
    return defense;
}

int Character::getSpeed() const {
    return speed;
}

bool Character::getIsPlayer() const {
    return isPlayer;
}

bool Character::getIsDefending() const {
    return isDefending;
}

bool Character::flee(Character* target) {
    if (this->speed > target->speed) {
        return true;
    }

    int chance = rand() % 100;
    return chance > 30;
}

void Character::defend() {
    defense *= 2;
    isDefending = true;
}

void Character::givePriority() {
    speed *= 100;
}

void Character::resetPriority() {
    speed /= 100;
}

void Character::heal() {
    health = originalHealth;
}

void Character::resetDefense() {
    defense /= 2;
    isDefending = false;
}

void Character::upgradeAttack() {
    attack += 2;
}

void Character::upgradeDefense() {
    defense += 2;
}

void Character::upgradeSpeed() {
    speed += 3;
}

std::string Character::toString() const {
    return "Name: " + name + "\nHealth: " + std::to_string(health) + "\nAttack: " + std::to_string(attack) +
           "\nDefense: " + std::to_string(defense) + "\nSpeed: " + std::to_string(speed);
}
