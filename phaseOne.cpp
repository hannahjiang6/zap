/*
 *  phaseOne.cpp
 *  Hannah Jiang (hjiang03)
 *  3/28/2023
 *
 *  CS 15 PROJECT 3 Zap
 *
 *  FILE PURPOSE:
 *  Implementation for the phaseOne.h file. Contains the tree functions, 
 *  count_freqs, serialize_tree, and deserialize_tree. All these 
 *  functions will be used in the main program of Zap to help serialize 
 *  and deserialize trees or creating a HuffmanTree
 * 
 */

#include "phaseOne.h"
#include <map>
#include <vector>
#include <iostream>

/*
 * name:      count_freqs 
 * purpose:   counts the frequencies of each character in the ASCII table
 * arguments: std::istream &text
 * returns:   none
 */
void count_freqs(std::istream &text) {
    std::map<char, int> wordCount;
    std::vector<char> charOrder;
    char c;

    while (text.get(c)) {
        if (!wordCount.count(c)) {
            charOrder.push_back(c);
        }
        wordCount[c]++;
    }

    for (auto &itr : charOrder) {
        std::cout << itr << ": " << wordCount[itr] << "\n";
    }
}

/*
 * name:      serialize_tree 
 * purpose:   serializes a HuffmanTree into a simple form of 
 *            Leaves vs. Internal Nodes
 * arguments: HuffmanTreeNode *root
 * returns:   a string of the serialized version of the HuffmanTree
 */
std::string serialize_tree(HuffmanTreeNode *root) {
    std::string str = "";

    if (root == nullptr) {
        return str;
    } else if (root->isLeaf()) {
        str += "L";
        str += root->get_val();
    } else {
        str += "I";
        str += serialize_tree(root->get_left());
        str += serialize_tree(root->get_right());
    }
    return str;
}

/*
 * name:      deserialize_tree 
 * purpose:   reads in a serialized tree string and calls a 
 *            helper function to create the HuffmanTree
 * arguments: std::string serial_tree
 * returns:   a HuffmanTreeNode pointing to the root of the tree
 */
HuffmanTreeNode *deserialize_tree(std::string serial_tree) {
    int index = 0;
    HuffmanTreeNode *root = tree_helper(serial_tree, index);
    return root;
}

/*
 * name:      tree_helper 
 * purpose:   reads in the serialized tree string and creates the 
 *            HuffmanTree from it
 * arguments: std::string serial_tree, int &index
 * returns:   a HuffmanTreeNode pointing to the root of the tree
 */
HuffmanTreeNode *tree_helper(std::string serial_tree, int &index) {
    int size = serial_tree.size();
    if (index >= size) {
        return nullptr;
    }

    char c = serial_tree[index];
    index++;

    if (c == 'L') {
        index++;
        return new HuffmanTreeNode(serial_tree[index-1], 0);
    } else if (c == 'I') {
        HuffmanTreeNode *left = tree_helper(serial_tree, index);
        HuffmanTreeNode *right = tree_helper(serial_tree, index);
        return new HuffmanTreeNode('\0', 0, left, right);
    } else {
        return nullptr;
    }
}