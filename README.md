# RBT-based Dictionary with Two Example Apps

This folder contains a Dictionary (RBT) ADT and
two client programs Order and WordFrequency. Order will give the
user-inputted dictionary as in-order and pre-order tree walk lists.
WordFrequency counts the occurrences of words in a given input file, storing them in an RBT Dictionary and printing the frequencies to the give output file. This Dictionary ADT'S RBT implemenation ensures correct formation, maintenance, and access of the dictionaries.

Usage:
$ ./Order <infile> <outfile> 
$ ./WordFrequency <infile> <outfile> 


Order.cpp             Source file for Order program
WordFrequency.cpp     Source file for WordFrequency program
Dictionary.cpp        Source file for Dictionary ADT
Dictionary.h          Header file for Dictionary ADT
DictionaryTest.cpp    Source file for Dictionary ADT testbench
Makefile              GNU Makefile with commands Order,WordFrequency DictionaryTest,clean, check
README.md             Description of folder contents and assignment

