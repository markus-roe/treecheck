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
int countNodes(Node *node);
bool isSubtree(Node *mainTree, Node *subtree);
std::string findNodePath(Node *node, int key, bool &found);
bool isSameStructure(Node *tree1, Node *tree2);
void deleteTree(Node *node);

int main()
{
    std::string command;
    std::string input;

    while (true)
    {
        std::cout << "Enter a command: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        ss >> command;

        if (command == "treecheck")
        {
            std::string param1, param2;
            ss >> param1;

            if (param1.empty())
            {
                std::cerr << "Usage: treecheck filename-suchbaum [filename-subtree]" << std::endl;
                continue;
            }

            std::ifstream inputFile(param1);
            if (!inputFile)
            {
                std::cerr << "Error opening input file: " << param1 << std::endl;
                continue;
            }

            Node *root = nullptr;
            int key;
            while (inputFile >> key)
            {
                root = insert(root, key);
            }
            inputFile.close();

            calculateBalanceFactors(root);

            printBalanceFactors(root);
            bool avl = isAVL(root);
            std::cout << "AVL: " << (avl ? "yes" : "no") << std::endl;

            int min = std::numeric_limits<int>::max();
            int max = std::numeric_limits<int>::min();
            int sum = 0;
            int count = 0;
            statistics(root, min, max, sum, count);
            double avg = static_cast<double>(sum) / count;
            std::cout << "min: " << min << ", max: " << max << ", avg: " << avg << std::endl;

            ss >> param2;
            if (!param2.empty())
            {
                std::ifstream subtreeFile(param2);
                if (!subtreeFile)
                {
                    std::cerr << "Error opening subtree file: " << param2 << std::endl;
                    continue;
                }

                Node *subtreeRoot = nullptr;
                while (subtreeFile >> key)
                {
                    subtreeRoot = insert(subtreeRoot, key);
                }
                subtreeFile.close();

                if (countNodes(subtreeRoot) == 1)
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
        }
        else
        {
            std::cerr << "Invalid command. Please enter 'treecheck' followed by the file names." << std::endl;
        }
    }

    return 0;
}

Node *insert(Node *node, int key)
{
    if (node == nullptr)
    {
        node = new Node{key, nullptr, nullptr};
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

int countNodes(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int height(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + std::max(height(node->left), height(node->right));
}

// int balanceFactor(Node *node)
// {
//     return height(node->right) - height(node->left);
// }

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

bool isAVL(Node *node)
{
    if (node == nullptr)
    {
        return true;
    }
    return std::abs(node->balanceFactor) <= 1 && isAVL(node->left) && isAVL(node->right);
}

void printBalanceFactors(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    printBalanceFactors(node->left);
    int bf = node->balanceFactor;
    std::cout << "bal(" << node->key << ") = " << bf;
    if (bf > 1 || bf < -1)
    {
        std::cout << " (AVL violation!)";
    }
    std::cout << std::endl;
    printBalanceFactors(node->right);
}

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

bool isSubtree(Node *mainTree, Node *subtree)
{
    if (subtree == nullptr)
    {
        return true;
    }
    if (mainTree == nullptr)
    {
        return false;
    }

    if (mainTree->key == subtree->key && isSameStructure(mainTree, subtree))
    {
        return true;
    }
    return isSubtree(mainTree->left, subtree) || isSubtree(mainTree->right, subtree);
}

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
