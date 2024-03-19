#include "contact.hpp"

void Book::display_contact(int i) {
    std::cout << "\n--- CONTACT " << i << " ---\n";
    std::cout << "Family name: " << contacts[i].get_family_name() << std::endl;
    std::cout << "Name: " << contacts[i].get_name() << std::endl;
    std::cout << "Phone number: " << contacts[i].get_phone_number() << std::endl;
    std::cout << std::endl;
}

void Book::display_contacts() {

    if (contacts.size() == 0) {
        std::cout << "Contact book is empty!\n";
        return;
    }

    for (int i = 0; i < contacts.size(); i++) {
        display_contact(i);
    }
}

void Book::search_contact() {

    std::string option;

    std::cout << "Insert either name, family_name or phone_number: ";
    std::cin.ignore();
    std::getline(std::cin, option);

    search_contact_index(option);

    for (int i = 0; i < results.size(); i++) {
        display_contact(results[i]);
    }
    results.clear();
}

void Book::insert_contact() {

    std::string family_name;
    std::string name;
    std::string phone_number;

    std::cout << "Enter family name: ";
    std::cin >> family_name;
    std::cout << "\nEnter name: ";
    std::cin >> name;
    std::cout << "\nEnter phone-number: ";
    std::cin >> phone_number;

    Contact contact(family_name, name, phone_number);

    contacts.push_back(contact);
}

void Book::search_contact_index(std::string option) {

    for (int i = 0; i < contacts.size(); i++) {
        if ( (contacts[i].get_family_name() == option)
            || (contacts[i].get_name() == option)
            || (contacts[i].get_phone_number() == option)
            ) {
            results.push_back(i);
        }
    }
}

void Book::delete_contact() {

    std::string option;
    int index_selected;

    std::cout << "\nInsert either name, family_name or phone_number: ";
    std::cin >> option;

    search_contact_index(option);

    for (int i = 0; i < results.size(); i++) {
        display_contact(results[i]);
    }

    std::cout << "\nChoose an index to delete: ";
    std::cin >> index_selected;

    contacts.erase(contacts.begin() + index_selected);
    std::cout << "\nDeleted contact " << index_selected << "\n";
}

void Book::save_book() {

    std::string filename;
    std::cout << "Write file to save to: ";
    std::cin >> filename;

    std::ofstream file_output(filename);
    
    for (int i = 0; i < contacts.size(); i++) {
        file_output << contacts[i].get_family_name() << "\n";
        file_output << contacts[i].get_name() << "\n";
        file_output << contacts[i].get_phone_number() << "\n";
    }
}

void Book::load_book() {

    std::string name;
    std::string family_name;
    std::string phone_number;

    std::string filename;
    std::cout<< "Write file to load from: ";
    std::cin >> filename;

    std::ifstream file_input(filename);
    contacts.clear();

    while (file_input >> family_name && file_input >> name && file_input >> phone_number) {
        Contact contact(family_name, name, phone_number);
        contacts.push_back(contact);
    }

}