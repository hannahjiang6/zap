/*
 *  phaseOne.h
 *  Hannah Jiang (hjiang03)
 *  3/28/2023
 *
 *  CS 15 PROJECT 3 Zap
 *
 *  FILE PURPOSE:
 *  Interface for phaseOne functions. Holds the functions that 
 *  will be used to in the offical implementation of the Zap project.
 * 
 */


#ifndef __PHASEONE_H__
#define __PHASEONE_H__

#include "HuffmanTreeNode.h"

#include <iostream>

void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(std::string serial_tree);
HuffmanTreeNode *tree_helper(std::string serial_tree, int &index);

#endif