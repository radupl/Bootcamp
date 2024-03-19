#include <string>
#include <iostream>

// Abstract general class
class Entity {
public:
    int defence_power;
    int health;
    std::string name;
    Entity(int defence, int health, std::string name) {
        this->defence_power = defence;
        this->health = health;
        this->name = name;
    } 

    virtual void attack(Entity& to_attack) = 0;
    virtual void defence(int damage_inflicted) = 0;
    virtual ~Entity() = default;
};

class Weapon {
protected:
    std::string name;
    int damage;
    Weapon(std::string name, int damage) { this->name = name; this->damage = damage; }
};

class Sword : public Weapon {
public:
    Sword(std::string name, int damage) : Weapon(name, damage) { std::cout << "Created sword!"; };
};

class Staff : public Weapon {
public:
    Staff(std::string name, int damage) : Weapon(name, damage) { std::cout << "Created staff!"; };
};

class Character : public Entity {
public:

    Weapon weapon_selected;
    Character(int defence_power, int health, std::string name, Weapon &weapon) : Entity(defence_power, health, name), weapon_selected(weapon) { std::cout << "Created character " << name; };
    void attack(Entity& entity) override;
    void defence(int damage_inflicted) override;
};