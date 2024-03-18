#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <set>

void add_elements_then_sort(std::string filename) {

    std::string word;
    std::map<std::string, int> word_count;

    // Opening the file
    std::ifstream input_file(filename); 
    if (!input_file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    // Read each word from the file
    while (std::cin >> word) {
        word_count[word]++;
    }

    // Vector for storing contents of the map
    std::vector<std::pair<std::string, int>> word_vector(word_count.begin(), word_count.end());

    // Sort the vector by the frequency
    std::sort(word_vector.begin(), word_vector.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    // Printing words and their frequency
    std::cout << std::endl << "COUNT " << " WORD" << std::endl;
    for (auto it = word_vector.begin(); it != word_vector.end(); it++) {
        std::cout << it->second << "      " << it->first << std::endl;
    } 
}

void insert_and_sort_simultaneously(std::string filename) {

    std::string word;
    // std::greater<first_argument> will invoke operator '>' and compare based on first argument of the pair (int)
    // In case of equality, it will compare second argument (std::string) lexicographically
    std::set<std::pair<int, std::string>, std::greater<std::pair<int, std::string>> > word_count;

    // Opening the file
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cout << "Error opening file: " << filename;
        return;
    }

    // Reading each word from the file
    while (input_file >> word) {
        auto it = word_count.begin();
        // Search the word from map
        while (it != word_count.end() && it->second != word) {
            it++;
        }

        // If it found the word, and didn't reach the end of the file
        if (it != word_count.end() && it->second == word) {

            // Save previous counter for the word
            int prev_count = it->first;
            // Erase the word-count pair
            word_count.erase(it);
            // Insert the same word with increased counter
            word_count.insert({prev_count + 1, word});
        // If it didn't find the word, insert it
        } else {
            word_count.insert({1, word});
        }
    }

    // Print the set
    std::cout << std::endl << "COUNT " << " WORD" << std::endl;
    for (auto it = word_count.begin(); it != word_count.end(); it++) {
        std::cout << it->first << "      " << it->second << std::endl; 
    }
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Synthax is: ./problem15 filename.txt\n";
        return 0;
    }

    std::string filename = argv[1];
    insert_and_sort_simultaneously(filename);
}