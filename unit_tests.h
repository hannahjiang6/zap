/*
 *  unit_tests.h
 *  Hannah Jiang (hjiang03)
 *  3/28/2023
 *
 *  CS 15 PROJECT 3 Zap
 *
 *  FILE PURPOSE:
 *  File to test cases for my program: Zap
 *
 */

#include "ZapUtil.h"
#include "HuffmanCoder.h"

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cassert>
#include <map>
#include <sstream>

// tests freq func (phaseOne)
void test_freq() {
    std::ifstream file("banana.txt");
    count_freqs(file);
}

// tests freq func (phaseOne)
void test_freq2() {
    std::ifstream file("hi.txt");
    count_freqs(file);
}

// tests freq func (phaseOne)
void test_freq3() {
    std::ifstream file("banana_apple.txt");
    count_freqs(file);
}

// tests freq func (phaseOne)
void test_freq4() {
    std::ifstream file("sentences.txt");
    count_freqs(file);
}

// tests serialization func (phaseOne)
void test_serialization() {
    HuffmanTreeNode *node1 = new HuffmanTreeNode('a', 2);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('b', 3);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('c', 100);
    HuffmanTreeNode *node4 = new HuffmanTreeNode('d', 60);
    HuffmanTreeNode *node5 = new HuffmanTreeNode('e', 4);
    HuffmanTreeNode *node6 = new HuffmanTreeNode('f', 5);

    HuffmanTreeNode *temp1 = new HuffmanTreeNode('\0', 5, node1, node2);
    HuffmanTreeNode *temp2 = new HuffmanTreeNode('\0', 9, node5, node6);
    HuffmanTreeNode *temp3 = new HuffmanTreeNode('\0', 160, node3, node4);
    HuffmanTreeNode *temp4 = new HuffmanTreeNode('\0', 14, temp1, temp2);
    HuffmanTreeNode *root = new HuffmanTreeNode('\0', 174, temp4, temp3);

    std::string s = serialize_tree(root);

    assert(s == "IIILaLbILeLfILcLd");
}

// tests deserialization func (phaseOne)
void test_deserialization() {
    std::cout << std::boolalpha << '\n';

    const char INTERNAL_NODE_VAL = '\0';

    HuffmanTreeNode *fig1Tree = makeFigure1Tree(INTERNAL_NODE_VAL);
    printTree(fig1Tree, INTERNAL_NODE_VAL);

    std::string s = serialize_tree(fig1Tree);
    assert(s == "IIILaLbILeLfILcLd");

    HuffmanTreeNode *tree1 = deserialize_tree(s);
    printTree(tree1, INTERNAL_NODE_VAL);
}

// tests creating nodes by printing them out
void test_createNodes() {
    HuffmanCoder tree;
    std::ifstream infile = tree.open_file("banana.txt");
    tree.count_freqs(infile);
    tree.createNodes();

    while(not tree.my_pq.empty()) {
        HuffmanTreeNode *curr = tree.my_pq.top();
        std::cerr << "Current top node contains character " 
                  << curr->get_val() << " and frequency " 
                  << curr->get_freq() << std::endl;

        tree.my_pq.pop();
    }
}

// tests creating huffman tree by printing out a tree (i created my own by hand 
// on paper and comapred it against what it printed out)
void test_createTree() {
    const char INTERNAL_NODE_VAL = '\0';

    HuffmanCoder tree;
    std::ifstream infile = tree.open_file("banana.txt");
    tree.count_freqs(infile);
    tree.createNodes();
    HuffmanTreeNode *root = tree.createHuffmanTree();
    
    printTree(root, INTERNAL_NODE_VAL);
}

// tests the generating codes binary strings by printing out (again created by 
// hand on paper and compared it against what it printed out)
void test_generateCodes() {
    HuffmanCoder tree;
    std::ifstream infile = tree.open_file("banana.txt");
    tree.count_freqs(infile);
    tree.createNodes();
    HuffmanTreeNode *root = tree.createHuffmanTree();
    tree.generateCodes(root, "");

    for(const auto& i : tree.encoding) {
        std::cout << i.first << " " << i.second << "\n";
    }
}

// test the serialization of the tree and asserted it produced what was expected
void test_serialization() {
    HuffmanCoder tree;
    std::ifstream infile = tree.open_file("banana.txt");
    tree.count_freqs(infile);
    tree.createNodes();
    HuffmanTreeNode *root = tree.createHuffmanTree();
    tree.generateCodes(root, "");
    std::string s = tree.serialize_tree(root);

    assert(s == "ILaILnILBLN");
}

// tests if the code was actually encoded into binary (compared it against 
// what ./the_zap program produced by printing it out)
void test_encodedText() {
    HuffmanCoder tree;
    std::ifstream infile = tree.open_file("banana.txt");
    tree.count_freqs(infile);
    infile.close();

    tree.createNodes();
    HuffmanTreeNode *root = tree.createHuffmanTree();
    tree.generateCodes(root, "");

    std::ifstream infile2 = tree.open_file("banana.txt");
    std::string binary_string = tree.encoded_file(infile2);
    infile2.close();

    std::cout << binary_string << "\n";

    std::cout << binary_string.length();
}

