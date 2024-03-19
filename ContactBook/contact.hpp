#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Contact {
    std::string name;
    std::string family_name;
    std::string phone_number;

public:
    Contact(std::string family_name, std::string name, std::string phone_number)
        : family_name(family_name), name(name), phone_number(phone_number) {};
    // Getters
    std::string get_name() { return this->name; };
    std::string get_family_name() { return this->family_name; };
    std::string get_phone_number() { return this->phone_number; };

    // Setters
    void set_name(std::string name) { this->name = name; };
    void set_family_name(std::string name) { this->family_name = family_name; };
    void set_phone_number(std::string phone_number) {this->phone_number = phone_number; }; 
};

class Book {
    std::vector<Contact> contacts;
    std::vector<int> results;
    void search_contact_index(std::string option);
    void display_contact(int index);
public:

    void display_contacts();
    void insert_contact();
    void save_book();
    void load_book();
    void delete_contact();
    void search_contact();
};

