#include "hob.hpp"

void Character::attack(Entity& entity) {
    //entity.health -= (entity. - entity.defence_power);
}

void Character::defence(int damage_inflicted) {
    health -= (damage_inflicted - defence_power);
}