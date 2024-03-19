#include "contact.hpp"

void display_menu() {

    std::cout << "--- MENU ---\n";
    std::cout << "0. Exit\n" 
        << "1. Display menu\n"
        << "2. Insert Contact\n"
        << "3. Display all Contacts\n"
        << "4. Save to file\n"
        << "5. Load file\n"
        << "6. Delete Contact\n"
        << "7. Search Contact\n";

}

int main() {

    int option;

    Book book;

    book.load_book();

    display_menu();

    while (option != 0) {

        std::cout << "Option: ";
        std::cin >> option;

        switch (option) {
            case 0:
                exit(EXIT_SUCCESS);
                break;
            case 1:
                display_menu();
                break;
            case 2:
                book.insert_contact();
                break;
            case 3:
                book.display_contacts();
                break;
            case 4:
                book.save_book();
                break;
            case 5:
                book.load_book();
                break;
            case 6:
                book.delete_contact();
                break;
            case 7:
                book.search_contact();
                break;
        }

        std::cout << "\nPress 1 to display menu\n";
    } 
}