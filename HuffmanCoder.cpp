/*
 *  HuffmanCoder.cpp
 *  Hannah Jiang (hjiang03)
 *  3/31/2023
 *
 *  CS 15 PROJECT 3 Zap
 *
 *  FILE PURPOSE:
 *  Implementation of the HuffmanCoder.h file. Holds all the code of what the 
 *  files do in the program. This file provides methods for encoding and 
 *  decoding files using the Huffman coding algorithm. The HuffmanCoder class 
 *  uses a priority queue to build the Huffman tree based on the frequency of 
 *  each character in the input file and then generates binary codes for each 
 *  character. It also provides the implementation for decoding the binary 
 *  output file back into the ASCII text using the Huffman tree.
 * 
 */


#include <iostream>
#include <queue>
#include <utility>
#include <sstream>
#include <fstream>

#include "HuffmanCoder.h"

/*
 * name:      encoder 
 * purpose:   encodes the input file into binary
 * arguments: std::string &input_file, std::string &output_file
 * returns:   none
 */
void HuffmanCoder::encoder(const std::string &input_file, 
                           const std::string &output_file) {
    BinaryIO binaryIO;

    // count the frequencies of the chars
    std::ifstream infile = open_file(input_file);
    count_freqs(infile);
    infile.close();

    // checking if the file had things that can be compressed
    if(wordCount.size() == 0) {
        std::cerr << input_file << " is empty and cannot be compressed.\n";
        exit(EXIT_FAILURE);
    }

    // create nodes/tree and generate the binary codes for each char
    createNodes();
    HuffmanTreeNode *root = createHuffmanTree();
    if (wordCount.size() > 1) {
        generateCodes(root, "");
    } else {
        one_node_code(root);
    }
    
    // encode the file into a string
    std::ifstream infile2 = open_file(input_file);
    std::string binary_string = encoded_file(infile2);
    infile2.close();

    std::string serializedCode = serialize_tree(root);
    // send it into pre-given binaryIO function
    binaryIO.writeFile(output_file, serializedCode, binary_string);

    // print out how many bits it took to code
    int N = binary_string.length();
    std::cout << "Success! Encoded given text using " << N << " bits.\n";
}

/*
 * name:      decoder 
 * purpose:   decodes the input_file given back into ASCII letters
 * arguments: std::string &input_file, std::string &output_file
 * returns:   none
 */
void HuffmanCoder::decoder(const std::string &input_file, 
                           const std::string &output_file) {
    std::pair<std::string, std::string> serial_tree;
    BinaryIO binaryIO;

    // get the information from the zapped file
    serial_tree = binaryIO.readFile(input_file);

    // create a huffman tree using the data from the file
    HuffmanTreeNode *root = deserialize_tree(serial_tree.first);

    // decode the file and send it into the output file
    std::ofstream outfile = open_output(output_file);

    // checks for special case of one node
    if (root->get_left() == nullptr and root->get_right() == nullptr) {
        one_node(root, serial_tree.second, outfile);
    } else {
        decode_file(root, serial_tree.second, outfile);
    }
    outfile.close();
}

/*
 * name:      encoded_file 
 * purpose:   finds the character in the encoding map which holds char and the 
 *            binary string and matches it up with the text, it turns the text 
 *            into a binary string
 * arguments: std::istream &text
 * returns:   std::string
 */
std::string HuffmanCoder::encoded_file(std::istream &text) {
    std::string encodedText = "";
    char c; 

    // gets the char in the text and turns it into binary
    while (text.get(c)) {
        for (auto i : encoding) {
            if (c == i.first) {
                encodedText += i.second;
            }
        }
    }
    return encodedText;
}

/*
 * name:      open_file 
 * purpose:   opens files and throws a runtime error if it could not be opened
 * arguments: std::string &filename
 * returns:   std::ifstream
 */
std::ifstream HuffmanCoder::open_file(const std::string &filename) {
    std::ifstream infile(filename);
    // opens a file
    if (not infile) {
        std::stringstream ss;
        ss << "Unable to open file " << filename;
        throw std::runtime_error(ss.str());
    }

    return infile;
}

/*
 * name:      createNodes
 * purpose:   creates nodes for a HuffmanTree which holds the character and 
 *            frequency end pushes it onto a priority queue
 * arguments: none
 * returns:   none
 */
void HuffmanCoder::createNodes() {
    // pushes nodes onto a priority_queue
    for (auto i : wordCount) {
        HuffmanTreeNode *newNode = new HuffmanTreeNode(i.first, i.second);
        my_pq.push(newNode);
    }
}

/*
 * name:      createHuffmanTree
 * purpose:   creates a HuffmanTree based on the nodes in the priority queue
 * arguments: none
 * returns:   HuffmanTreeNode *root
 */
HuffmanTreeNode* HuffmanCoder::createHuffmanTree() {
    if (my_pq.size() == 1) {
        return my_pq.top();
    }

    while (my_pq.size() != 1) {
        // takes the top 2 nodes of the priority_queue
        HuffmanTreeNode *node1 = my_pq.top();
        my_pq.pop();
        HuffmanTreeNode *node2 = my_pq.top();
        my_pq.pop();
        // uses the freq of the 2 nodes to create a parent_node
        int frequency = node1->get_freq() + node2->get_freq();
        HuffmanTreeNode *p = new HuffmanTreeNode('\0', frequency, node1, node2);
        // pushes parent onto the priority_queue
        my_pq.push(p);
    }
    // return the root of the tree
    return my_pq.top();
}

/*
 * name:      generateCodes 
 * purpose:   generates the binary codes for the HuffmanTree
 * arguments: HuffmanTreeNode *root, std::string code
 * returns:   none
 */
void HuffmanCoder::generateCodes(HuffmanTreeNode *root, std::string code) {
    // base case
    if (root == nullptr) {
        return;
    } else if (root->isLeaf()) {
        // creates the binary code for the char and stores it into a map
        encoding[root->get_val()] = code;
    } else {
        // recurse through the huffman tree until it finds a leaf node
        generateCodes(root->get_left(), code + "0");
        generateCodes(root->get_right(), code + "1");
    }
}

/*
 * name:      one_node_code 
 * purpose:   generates the binary codes for the HuffmanTree for the special 
 *            case of having only one node
 * arguments: HuffmanTreeNode *root
 * returns:   none
 */
void HuffmanCoder::one_node_code(HuffmanTreeNode *root) {
    if (root->get_left() == nullptr and 
        root->get_right() == nullptr) { 
        // only one node in the tree, set its code to 0
        encoding[root->get_val()] = "0";
        return;
    }
}

/*
 * name:      decode_file 
 * purpose:   goes through the entire serial_tree string and turns it back into 
 *            ASCII
 * arguments: HuffmanTreeNode *root, std::string serial_tree, const 
 *            std::string &output_file, int index
 * returns:   none
 */
void HuffmanCoder::decode_file(HuffmanTreeNode *root, std::string serial_tree, 
                               std::ostream &output_file) {
    int length = serial_tree.length();
    // base case
    if (root == nullptr or length <= 0) {
        return;
    }
    // temp variable so root is not changed
    HuffmanTreeNode *temp = root;

    for (int i = 0; i < length; i++) {
        int num = serial_tree[i] - '0';
        // goes through the tree
        if (num == 0) {
            temp = temp->get_left();
        } else if (num == 1) {
            temp = temp->get_right();
        }
        // throws error if the binary code ends up in the middle of the tree
        if (i == length-1 and not temp->isLeaf()) {
            throw std::runtime_error("Encoding did not match Huffman tree.");
        }
        // gets the char and send it into the output_file
        if (temp->isLeaf()) {
            output_file << temp->get_val();
            temp = root; // goes back to the root of the tree
        }
    }
}

/*
 * name:      one_node 
 * purpose:   goes through the entire serial_tree string and turns it back into 
 *            ASCII (special case for one HuffmanTreeNode)
 * arguments: HuffmanTreeNode *root, std::string serial_tree, const 
 *            std::string &output_file, int index
 * returns:   none
 */
void HuffmanCoder::one_node(HuffmanTreeNode *root, std::string serial_tree, 
                            std::ostream &output_file) {
    int length = serial_tree.length();

    // base case
    if (root == nullptr or length <= 0) {
        return;
    }

    for (int i = 0; i < length; i++) {
        output_file << root->get_val();
    }                      
}

/*
 * name:      open_file 
 * purpose:   opens files and throws a runtime error if it could not be opened
 * arguments: std::string &filename
 * returns:   std::ifstream
 */
std::ofstream HuffmanCoder::open_output(const std::string &filename) {
    std::ofstream outfile(filename, std::ios::out);

    if (not outfile) {
        std::stringstream ss;
        ss << "Unable to open file " << filename;
        throw std::runtime_error(ss.str());
    }

    return outfile;
}

/*
 * name:      count_freqs 
 * purpose:   counts the frequencies of each character in the ASCII table
 * arguments: std::istream &text
 * returns:   none
 */
void HuffmanCoder::count_freqs(std::istream &text) {
    char c;
    // goes through the entire text and stores count/char into a map
    while (text.get(c)) {
        if (not wordCount.count(c)) {
            charOrder.push_back(c);
        }
        wordCount[c]++;
    }
}

/*
 * name:      serialize_tree 
 * purpose:   serializes a HuffmanTree into a simple form of 
 *            Leaves vs. Internal Nodes
 * arguments: HuffmanTreeNode *root
 * returns:   a string of the serialized version of the HuffmanTree
 */
std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) {
    std::string str = "";
    // base case
    if (root == nullptr) {
        return str;
    } else if (root->isLeaf()) {
        // string "L" for leaf node and string the char after
        str += "L";
        str += root->get_val();
    } else {
        // serialize the internal node and continue to recurse through the tree
        str += "I";
        str += serialize_tree(root->get_left());
        str += serialize_tree(root->get_right());
    }
    // returns a serialized string of the tree
    return str;
}

/*
 * name:      deserialize_tree 
 * purpose:   reads in a serialized tree string and calls a 
 *            helper function to create the HuffmanTree
 * arguments: std::string serial_tree
 * returns:   a HuffmanTreeNode pointing to the root of the tree
 */
HuffmanTreeNode* HuffmanCoder::deserialize_tree(std::string serial_tree) {
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
HuffmanTreeNode* HuffmanCoder::tree_helper(std::string serial_tree, int &index){
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