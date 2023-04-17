#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <sstream>

struct Node
{
    int key;
    Node *left;
    Node *right;
    int balanceFactor;
};

// Prototypes
Node *insert(Node *node, int key);
int height(Node *node);
void calculateBalanceFactors(Node *node);
bool isAVL(Node *node);
void printBalanceFactors(Node *node);
void statistics(Node *node, int &min, int &max, int &sum, int &count);
bool isSubtree(Node *mainTree, Node *subtree);
std::string findNodePath(Node *node, int key, bool &found);
bool isSameStructure(Node *tree1, Node *tree2);
void deleteTree(Node *node);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [filename-suchbaum] [filename-subtree]" << std::endl;
        return 1;
    }

    std::string param1 = argv[1];
    std::string param2;

    if (argc == 3)
    {
        param2 = argv[2];
    }

    // Read the main tree file
    std::ifstream inputFile(param1);
    if (!inputFile)
    {
        std::cerr << "Error opening input file: " << param1 << std::endl;
        return 1;
    }

    // Insert keys into the main tree
    Node *root = nullptr;
    int key;
    while (inputFile >> key)
    {
        root = insert(root, key);
    }
    inputFile.close();

    // Calculate balance factors
    calculateBalanceFactors(root);

    // Print balance factors
    printBalanceFactors(root);

    // Check if the tree is an AVL tree
    bool avl = isAVL(root);
    std::cout << "AVL: " << (avl ? "yes" : "no") << std::endl;

    // Calculate and print tree statistics
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    int sum = 0;
    int count = 0;
    statistics(root, min, max, sum, count);
    double avg = static_cast<double>(sum) / count;
    std::cout << "min: " << min << ", max: " << max << ", avg: " << avg << std::endl;

    // Read the subtree file (if provided)
    if (!param2.empty())
    {
        std::ifstream subtreeFile(param2);
        if (!subtreeFile)
        {
            std::cerr << "Error opening subtree file: " << param2 << std::endl;
            return 1;
        }

        // Insert keys into the subtree
        Node *subtreeRoot = nullptr;
        int subtreeCounter = 0;
        while (subtreeFile >> key)
        {
            subtreeRoot = insert(subtreeRoot, key);
            subtreeCounter++;
        }
        subtreeFile.close();

        // Check if the subtree is present in the main tree
        if (subtreeCounter == 1)
        {
            bool found = false;
            std::string path = findNodePath(root, subtreeRoot->key, found);
            if (found)
            {
                std::cout << subtreeRoot->key << " found " << path << std::endl;
            }
            else
            {
                std::cout << subtreeRoot->key << " not found!" << std::endl;
            }
        }
        else
        {
            bool subtreeFound = isSubtree(root, subtreeRoot);
            std::cout << (subtreeFound ? "Subtree found" : "Subtree not found!") << std::endl;
        }

        deleteTree(subtreeRoot);
    }
    deleteTree(root);

    return 0;
}

// Insert a key into a binary search tree
Node *insert(Node *node, int key)
{
    if (node == nullptr)
    {
        node = new Node{key, nullptr, nullptr, -1};
    }
    else if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }
    return node;
}

// Calculate the height of a binary tree
int height(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + std::max(height(node->left), height(node->right));
}

// Calculate the balance factors of all nodes in the tree
void calculateBalanceFactors(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    calculateBalanceFactors(node->left);
    calculateBalanceFactors(node->right);

    node->balanceFactor = height(node->right) - height(node->left);
}

// Check if a binary tree is an AVL tree
bool isAVL(Node *node)
{
    if (node == nullptr)
    {
        return true;
    }
    return std::abs(node->balanceFactor) <= 1 && isAVL(node->left) && isAVL(node->right);
}

// Print the balance factors of all nodes in the tree
void printBalanceFactors(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    printBalanceFactors(node->right);
    printBalanceFactors(node->left);
    int bf = node->balanceFactor;
    std::cout << "bal(" << node->key << ") = " << bf;
    if (bf > 1 || bf < -1)
    {
        std::cout << " (AVL violation!)";
    }
    std::cout << std::endl;
}

// Calculate tree statistics (min, max, sum, count)
void statistics(Node *node, int &min, int &max, int &sum, int &count)
{
    if (node == nullptr)
    {
        return;
    }
    statistics(node->left, min, max, sum, count);
    min = std::min(min, node->key);
    max = std::max(max, node->key);
    sum += node->key;
    count++;
    statistics(node->right, min, max, sum, count);
}

// Check if a subtree is present in a main tree
bool isSubtree(Node *mainTree, Node *subtree)
{
    // Check if the main tree and subtree have the same structure and values,
    // or if the subtree is present in the left or right subtree of the main tree
    return (mainTree != nullptr) && (isSameStructure(mainTree, subtree) || isSubtree(mainTree->left, subtree) || isSubtree(mainTree->right, subtree));
}

// Check if a subtree is present in a main tree, or if the main tree has the same structure and values as the subtree
bool isSameStructure(Node *tree1, Node *tree2)
{
    if (tree2 == nullptr)
    {
        return true;
    }
    if (tree1 == nullptr)
    {
        return false;
    }
    if (tree1->key == tree2->key &&
        isSameStructure(tree1->left, tree2->left) &&
        isSameStructure(tree1->right, tree2->right))
    {
        return true;
    }
    return isSameStructure(tree1->left, tree2) || isSameStructure(tree1->right, tree2);
}

// Find the path from the root to a node with the specified key in a binary search tree
// and set the 'found' flag to true if the key is found
std::string findNodePath(Node *node, int key, bool &found)
{
    if (node == nullptr)
    {
        return "";
    }

    if (node->key == key)
    {
        found = true;
        return std::to_string(key);
    }

    std::string leftPath = findNodePath(node->left, key, found);
    if (found)
    {
        return std::to_string(node->key) + ", " + leftPath;
    }

    std::string rightPath = findNodePath(node->right, key, found);
    if (found)
    {
        return std::to_string(node->key) + ", " + rightPath;
    }

    return "";
}

// Recursively delete a binary tree and free its memory
void deleteTree(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
