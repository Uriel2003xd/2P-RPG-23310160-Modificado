//
// Created by Victor Navarro on 15/02/24.
//

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
protected:
    std::string name;
    int health;
    int originalHealth;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    bool isDefending = false;

public:
    Character(const std::string& _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer);

    virtual void doAttack(Character* target) = 0;
    virtual void takeDamage(int damage) = 0;

    void defend();
    void resetDefense();
    void upgradeAttack();
    void upgradeDefense();
    void upgradeSpeed();
    void resetPriority();
    void givePriority();
    bool flee(Character* target);
    const std::string& getName() const;
    int getHealth() const;
    int getOriginalHealth() const;
    int getAttack() const;
    int getDefense() const;
    int getSpeed() const;
    bool getIsPlayer() const;
    bool getIsDefending() const;
    std::string toString() const;
    void heal();
};

#endif // CHARACTER_H
