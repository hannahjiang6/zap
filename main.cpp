/*
 *  main.cpp
 *  Hannah Jiang (hjiang03)
 *  3/31/2023
 *
 *  CS 15 PROJECT 3 Zap
 *
 *  FILE PURPOSE:
 *  Runs the huffman compression program known as "zap". Through the provided
 *  inputs, the program will do 1 of 3 things. Either compress the files (zap),
 *  decompress the files (unzap), or throw an error if the inputs were not 
 *  valid.
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "HuffmanCoder.h"


using namespace std;

int main(int argc, char *argv[])
{
    // check for valid input
    if (argc != 4) {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        exit(EXIT_FAILURE);
    }

    HuffmanCoder my_HuffmanCoder;

    // strings the input and output file to send into the program
    string inputFile = argv[2];
    string outputFile = argv[3];

    // checks what the first command is
    string command = argv[1];

    // making sure it's a valid command else it throws an error
    if (command == "zap") {
        my_HuffmanCoder.encoder(inputFile, outputFile);
    } else if (command == "unzap") {
        my_HuffmanCoder.decoder(inputFile, outputFile);
    } else {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        exit(EXIT_FAILURE);
    }

    return 0;
}