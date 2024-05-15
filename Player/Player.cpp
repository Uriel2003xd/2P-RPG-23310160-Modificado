//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>
#include <fstream>

using namespace std;

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}
Player::Player(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _level, int _experience) : Character(_name, _health, _attack, _defense, _speed, _isPlayer) {
    level = _level;
    experience = _experience;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);

    if (target->getHealth() <= 0)
    {
        auto enemyTarget = dynamic_cast<Enemy*>(target);

        if (enemyTarget != nullptr) {
            gainExperience(enemyTarget->getExperience());
        }
    }
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if (trueDamage < 0) {
        trueDamage = 0;
    }

    health-= trueDamage;
    if(health <= 0) {
        health = 0;
    }

    cout << name << " Recibio " << trueDamage << " De Ataque!" << endl;
    cout << name << " Tiene " << health << " Salud Restante " << endl;

    if(health <= 0) {
        cout << name << " Ha Sido Derrotado!" << endl;
    }

}




void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Selecciona al enemigo que vas atacar: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    while (true) {
        cout << getName() << "\nSigue el turno de: " << endl
             << "Que vas a decidir? " << endl
             << "1. Attacar" << endl
             << "2. Defender" << endl;
        cin >> action;
        if (action == 1 || action == 2) {
            break;
        } else {
            cout << "Accion no valida" << endl;
        }
    }
    Action currentAction;
    Character* target = nullptr;

    if (getIsDefending()) {
        resetDefense();
    }

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.target = this;
            currentAction.action = [this](){
                defend();
            };
            currentAction.speed = DEFENSE_SPEED_PRIORITY;
            break;
        default:
            cout << "Accion no valida" << endl;
            break;
    }

    return currentAction;
}
// Level functions

void Player::levelUp() {
    level++;
    cout << getName() << " Has Alcanzado El Nivel ( " << level << ")" << endl;

    upgradeStats();
}

void Player::upgradeStats() {

    int statOption;
    while(true) {
        cout << "\n Escoge una mejora para el jugador: " << getName() << ":" << endl;
        cout << "1. Ataque" << endl << "2. Defensa" << endl << "3. Velocidad" << endl;
        cin >> statOption;

        if (statOption > 0 && statOption < 4) {
            break;
        }
        else {
            cout << "Opcion no valida" << endl;
        }
    }

    int prevAttack, prevDefense, prevSpeed;

    switch (statOption) {
        case 1:
            prevAttack = getAttack();
            upgradeAttack();
            cout << getName() << " Incremento El Ataque de " << prevAttack << " a " << getAttack() << endl;
            break;
        case 2:
            prevDefense = getDefense();
            upgradeDefense();
            cout << getName() << " Incremento Su Defensa de " << prevDefense << " a " << getDefense() << endl;
            break;
        case 3:
            prevSpeed = getSpeed();
            upgradeSpeed();
            cout << getName() << " Aumento Su Velocidad de " << prevSpeed << " a " << getSpeed() << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
    }
}

void Player::serialize(const char* filename) {
    std::ofstream file(filename); {
        if (file.is_open()) {
            file << name << std::endl;
            file << originalHealth << std::endl;
            file << attack << std::endl;
            file << defense << std::endl;
            file << speed << std::endl;
            file << isPlayer << std::endl;
            file << level << std::endl;
            file << experience << std::endl;
        } else {
            std::cout << "Error al abrir archivo" << std::endl;
        }
    }
}

// Unserialize the player's attributes
void Player::unserialize(const char *filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> name;
        file >> originalHealth;
        health = originalHealth;
        file >> attack;
        file >> defense;
        file >> speed;
        file >> isPlayer;
        file >> level;
        file >> experience;
        file.close();

        cout << "El Personaje Se Ha Sido Cargado Con Exito" << endl;
        cout << toString() << endl;
    } else {
        std::cerr << "Este archivo no se puede abrir por que no se encontro, Intenta De Nuevo Creando Un Personaje" << std::endl;
        while (true) {
            cout << "Introduce El Nombre Del Personaje: ";
            cin >> name;
            cout << "Estas Seguro De Usar Este Nombre? " << name << "? (s/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 's') {
                break;
            }
        }
        originalHealth = 100;
        health = originalHealth;
        attack = 20;
        defense = 5;
        speed = 10;
        isPlayer = true;
        level = 1;
        experience = 0;
    }
}