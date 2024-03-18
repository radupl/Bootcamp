#include <iostream>
#include <fstream>
#include "p15_3.hpp"

#define SPACE 10

// Insert words from a file
void BST::insert_data(std::string& filename) {
    std::string w;
    std::ifstream input_file(filename);
    while (input_file >> w) {
        // Populating frequency map
        word_count[w]++;
    }

    // EOF-bit is set on error after finishing reading the file
    // Reset error state flags
    input_file.clear();
    // Reset the position to the beginning of the file
    input_file.seekg(0, input_file.beg);

    // Read from the file and insert each word in the corresponding node
    while (input_file >> w) {
        insert(root, w);
    }
}

// Function for printing the tree in 2D
void BST::bst_2D(Node*& node, int space) {

    if (node == NULL) {
        return;
    }

    // Space between each level of the tree
    space += SPACE;
    
    bst_2D(node->right, space);

    std::cout << std::endl;

    for (int i = SPACE; i < space; i++) {
        std::cout << " ";
    }

    std::cout << "->" << node->word << "(" << node->count << ")" << std::endl;

    bst_2D(node->left, space);
}

void BST::print_bst_2D() {
    bst_2D(root, 0);
}

void BST::print_bst_1D() {
    std::cout << "-COUNT-    " << "-WORD-" << std::endl;
    traverse_bst_inorder(root);
}

// Insert each word in the correct node of the tree.
void BST::insert(Node*& node, std::string& word) {

    // If the node doesn't exist, create one.
    if (!node) {
        node = new Node(word);
    // If the frequency of the node to insert is greater than the frequency of the root, insert in right node
    } else if (word_count[word] > word_count[node->word]) {
        insert(node->right, word);
    // If the frequency of the node to insert is less than the frequency of the root, insert in left node
    } else if (word_count[word] < word_count[node->word]) {
        insert(node->left, word);
    // If frequencies are equal, and it is the same word, increase its frequency
    } else if (word == node->word){
         node->count++;
    // If frequencies are equal but is a new word, insert in left node (could be right node as well)
    } else {
        insert(node->left, word);
    }
}

// For printing the tree Value - Word
void BST::traverse_bst_inorder(Node*& node) {
    if (node) {
        // Traverse right node
        traverse_bst_inorder(node->right);
        // Traverse root
        std::cout << node->count << "           " << node->word << std::endl;
        // Traverse left node
        traverse_bst_inorder(node->left);
    } 
}

int main(int argc, char* argv[]) {

    BST tree;

    std::string filename = argv[1];

    tree.insert_data(filename);
    tree.print_bst_2D();
    std::cout << std::endl;
    tree.print_bst_1D();

    return 0;
}