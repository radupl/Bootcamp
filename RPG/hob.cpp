#include <stdint.h>
#include "hob.hpp"

void create_warrior() {
    Sword sword("Sword", 20);
    Character character(10, 100, "Warrior", sword);

}

void start_game() {

    uint8_t character_pick;

    std::cout << "---------- GAME START ----------\n";
    std::cout << "\n Choose your Character: \n"
        << "1. Warrior\n"
        << "2. Mage\n";
    std::cin >> character_pick;

    switch (character_pick) {
        case 1:
        {
            create_warrior();
            break;
        }
        case 2: 
        {
            Staff staff("Staff", 35);
            Character character(5, 80, "Mage", staff);
            break;
        }
        default:
            break;
    }
}

int main() {

    start_game();
    return 0;
    
}