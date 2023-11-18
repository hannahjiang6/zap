/*
 *  HuffmanCoder.h
 *  Hannah Jiang (hjiang03)
 *  3/31/2023
 *
 *  CS 15 PROJECT 3 Zap
 *
 *  FILE PURPOSE:
 *  Interface for the HuffmanCoder.cpp file. It holds all the functions that 
 *  will be used for processing a file into binary and then unprocessing it 
 *  back into an ASCII file.
 * 
 */


#ifndef __HUFFMANCODER_H__
#define __HUFFMANCODER_H__

#include "HuffmanTreeNode.h"
#include "BinaryIO.h"

#include <map>
#include <vector>
#include <queue>


class HuffmanCoder {
public:

    void encoder(const std::string &input_file, const std::string &output_file);
    void decoder(const std::string &input_file, const std::string &output_file);

private:

    // private variables
    std::map<char, int> wordCount;
    std::vector<char> charOrder;
    std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, 
                        NodeComparator> my_pq;
    std::map<char, std::string> encoding;

    // encoder functions
    std::ifstream open_file(const std::string &filename);
    void count_freqs(std::istream &text);
    void createNodes();
    HuffmanTreeNode* createHuffmanTree();
    void generateCodes(HuffmanTreeNode *root, std::string code);
    std::string serialize_tree(HuffmanTreeNode *root);
    std::string encoded_file(std::istream &text);
    void one_node_code(HuffmanTreeNode *root);

    // decoder functions
    void decode_file(HuffmanTreeNode *root, std::string serial_tree, 
                     std::ostream &output_file);
    std::ofstream open_output(const std::string &filename);
    HuffmanTreeNode *deserialize_tree(std::string serial_tree);
    HuffmanTreeNode *tree_helper(std::string serial_tree, int &index);
    void one_node(HuffmanTreeNode *root, std::string serial_tree, 
                  std::ostream &output_file);
};


#endif