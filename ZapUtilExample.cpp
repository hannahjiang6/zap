/*
Example driver program to demonstrate the functionality of the ZapUtil module.

Example Makefile rules:

ZapUtilExample.o: ZapUtilExample.cpp ZapUtil.h HuffmanTreeNode.h
ZapUtilExample.out: ZapUtilExample.o HuffmanTreeNode.o ZapUtil.o
    clang++ -g3 -o $@ $^

WARNING: If you run an executable compiled from this program with valgrind it
will report a memory leak. This is because we allocate heap memory (directly and
via makeFigure1Tree) that is never freed in this code. You will need to write
your own function to free a tree as part of the assignment, hence one is not
provided.

Author: Chami Lamelas (slamel01)
Date: Jan 2023
*/

#include <iostream>

#include "HuffmanTreeNode.h"
#include "ZapUtil.h"

int main() {
    // Handy C++ trick to make true and false actually print instead of 0 and 1
    // respectively (newline for spacing)
    std::cout << std::boolalpha << '\n';

    // Value of your choice (good to put in a constant)
    const char INTERNAL_NODE_VAL = '\0';

    // Makes a tree based on figure 1 and prints it
    HuffmanTreeNode *fig1Tree = makeFigure1Tree(INTERNAL_NODE_VAL);
    printTree(fig1Tree, INTERNAL_NODE_VAL);

    // Makes another tree based on figure 1 that will have same structure,
    // values, and frequencies. Print statement below demonstrates that no
    // pointer equality is done by treeEquals.
    HuffmanTreeNode *anotherFig1Tree = makeFigure1Tree(INTERNAL_NODE_VAL);
    std::cout << "2 Trees with Figure 1 nodes equal? "
              << treeEquals(fig1Tree, anotherFig1Tree, true) << '\n';
    std::cout << "Figure 1 tree equal to empty tree? "
              << treeEquals(fig1Tree, nullptr, true) << '\n';

    // Now, let's see what happens when checkFrequency is false. Let's create 2
    // small trees with identical structure and values but not frequencies.
    HuffmanTreeNode *tinyTree = new HuffmanTreeNode(INTERNAL_NODE_VAL, 2);
    tinyTree->set_left(new HuffmanTreeNode('a', 1));
    tinyTree->set_right(new HuffmanTreeNode('b', 1));
    HuffmanTreeNode *tinyTreeNoFreq =
        new HuffmanTreeNode(INTERNAL_NODE_VAL, -1);
    tinyTreeNoFreq->set_left(new HuffmanTreeNode('a', -1));
    tinyTreeNoFreq->set_right(new HuffmanTreeNode('b', -1));
    std::cout << "\n2 tiny trees equal? "
              << treeEquals(tinyTree, tinyTreeNoFreq, false) << '\n';

    // But, as shown below if we create a tiny tree that differs in value or
    // structure, it fails
    HuffmanTreeNode *tinyTreeDiffVals =
        new HuffmanTreeNode(INTERNAL_NODE_VAL, 2);
    tinyTree->set_left(new HuffmanTreeNode('c', 1));
    tinyTree->set_right(new HuffmanTreeNode('d', 1));
    std::cout << "2 tiny trees with different values? "
              << treeEquals(tinyTree, tinyTreeDiffVals, false) << '\n';
    std::cout << "Tiny tree and empty tree? "
              << treeEquals(tinyTree, nullptr, false) << '\n';

    return 0;
}