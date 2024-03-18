#include <iostream>
#include <fstream>
#include <unistd.h>
#include "problem16.hpp"

// Function for opening the file
void TextEditor::open_file() {

    // Clear the file in case of opening another file.
    file.clear();

    std::string filename;
    std::cout << "Enter the name of the file to open: ";
    std::cin >> filename;

    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        std::cout << "Error opening file: " << filename;
        return; 
    }

    std::cout << "File opened!" << std::endl;

    // Getting each line from file and populating the std::vector file.
    std::string line;
    while (getline(input_file, line)) {
        file.push_back(line);
    }

    // Save the state of the file opened.
    undo = file;

    // Get the name of the file.
    file_opened = filename;    
}

// Function for displaying the file
void TextEditor::display_file() {

    std::cout << " ----------- FILE CONTENT ----------- " << std::endl;

    std::cout << "            - " << file_opened << " -" << std::endl;

    for (std::string line : file) {
        std::cout << line << std::endl;
    }
}

void TextEditor::write_text_at_position() {

    int position;

    std::string text;

    std::cout << "Enter the position you want to write to: ";

    std::cin >> position;

    // If the position is not in the boundaries of the file.
    if (position < 0 || position > file.size()) {
        std::cout << "Invalid position. Please write a position between 0 and " << file.size() << std::endl;
        return;
    }
    
    std::cout << std::endl << "Enter the text: ";

    // For ignoring the newline from pressing "enter"
    std::cin.ignore(); 

    getline(std::cin, text);

    // Save the state of the file before modifying it
    undo = file;

    // Insert text at position specified
    file.insert(file.begin() + position, text);
}

void TextEditor::delete_text_from_position() {

    int line_position;
    int pos_in_line;
    int num_of_characters;

    std::cout << "Enter the line position for deletion: ";
    std::cin >> line_position;
    std::cout << std::endl << "Enter the position in the string from which to delete: ";
    std::cin >> pos_in_line;
    std::cout << std::endl << "Enter number of characters to delete: ";
    std::cin >> num_of_characters;
    std::cout << std::endl;

    // Save the state of the file before modifying it
    undo = file;
    
    // Erase 'num_of_characters' characters starting from position 'pos_in_line' at the specified line
    // If resulted string is empty, remove the whole element from vector 'file'.
    std::string line = (file.begin() + line_position)->erase(pos_in_line, num_of_characters);
    if (line == "") {
        file.erase(file.begin() + line_position);
    }
}

void TextEditor::undo_action() {

    // Redo takes the state of the file before undoing
    redo = file;

    // File takes the state of undo
    file = undo;

    std::cout << "Undo action done!" << std::endl;
}

void TextEditor::redo_action() {

    // File takes the state of redo
    file = redo;

    std::cout << "Redo action done!" << std::endl;
}

void TextEditor::save_to_file() {

    // ofstream::trunc for deleting the contents of the opened file.
    // out flag is present by default but overridden if used only trunc.
    std::ofstream input_file(file_opened, std::ofstream::out | std::ofstream::trunc);

    if (!input_file.is_open()) {
        std::cout << "Error opening file" << file_opened << "for saving";
    }
    
    // Write each line from vector 'file' into the file.
    for (std::string line : file) {
        input_file << line << std::endl;
    }

}

void display_menu() {
    std::cout<< std::endl << " ----------- SELECT AN OPTION FROM THE MENU ----------- " << std::endl
            << "0. Display menu" << std::endl
            << "1. Open file" << std::endl
            << "2. Display file" << std::endl
            << "3. Write text at position" << std::endl
            << "4. Delete text from position" << std::endl
            << "5. Save modification to the current file" << std::endl
            << "6. Undo last insertion or deletion" << std::endl
            << "7. Redo last undo" << std::endl
            << "8. Exit" << std::endl;
}

int main() {

    TextEditor text_editor;
    int option;

    display_menu();

    while (1) {

        std::cout << "Option: ";
        std::cin >> option;

        switch (option) {
            case 0:
                display_menu();
                break;
            case 1:
                text_editor.open_file();
                sleep(1);
                break;
            case 2:
                text_editor.display_file();
                sleep(1);
                break;
            case 3:
                text_editor.write_text_at_position();
                sleep(1);
                break;
            case 4:
                text_editor.delete_text_from_position();
                sleep(1);
                break;
            case 5:
                text_editor.save_to_file();
                sleep(1);
                break;
            case 6: 
                text_editor.undo_action();
                sleep(1);
                break;
            case 7: 
                text_editor.redo_action();
                sleep(1);
                break;
            case 8:
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }

        std::cout << std::endl << "Press 0 to display menu" << std::endl;
    }
    
    return 0;
}