###
### Makefile for zap Project
### zap is a huffman compression program
###
### Author:  Hannah Jiang (hjiang03)

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# Compiles Zap
zap: main.o HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o
	$(CXX) $(LDFLAGS) -o zap main.o HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o

# This rule builds main.o
main.o: main.cpp HuffmanCoder.h ZapUtil.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds HuffmanCoder.o
HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h BinaryIO.h HuffmanTreeNode.h
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp

# This rule builds phaseOne.o
phaseOne.o: phaseOne.cpp phaseOne.h 
	$(CXX) $(CXXFLAGS) -c phaseOne.cpp

# Compiles and runs unit_test
unit_test: unit_test_driver.o HuffmanTreeNode.o ZapUtil.o HuffmanCoder.o BinaryIO.o
	$(CXX) $(CXXFLAGS) $^


# # This rule provides my final submission 
provide:
	provide comp15 proj3_zap \
				   unit_tests.h README Makefile \
				   HuffmanCoder.cpp HuffmanCoder.h \
				   HuffmanTreeNode.h main.cpp \
				   empty_file.txt no_nodes.txt \
				   one_node.txt space_char.txt

clean: 
	rm phaseOne.o HuffmanCoder.o main.o *~ a.out