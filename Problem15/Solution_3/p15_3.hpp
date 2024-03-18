#include <string>
#include <map>

class Node {
public:
    int count;
    std::string word;
    Node* left;
    Node* right;
    Node(std::string& w) : count(1), word(w), left(nullptr), right(nullptr) {};
};

class BST {
private:
    Node* root;
    std::map<std::string, int> word_count;
    void insert(Node*& root, std::string& word);
    void traverse_bst_inorder(Node*& root);
    void bst_2D(Node*& node, int space);
public:
    BST() : root(nullptr) {};
    void insert_data(std::string& filename);
    void print_bst_2D();
    void print_bst_1D();
};

