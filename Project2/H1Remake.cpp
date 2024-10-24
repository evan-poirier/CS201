// Name: Evan Poirier
// Email: espoirier@crimson.ua.edu
// Course Section: Fall 2024 CS 201
// Homework #: 2
// To Compile: g++ -std=c++20 H1Remake.cpp
// To Run: ./a.exe < input.txt
//
// Notes:
// Rather than printing to the terminal, this program creates an output.txt file
// with total, unique total, and individual word counts. 
// I did this because on my PC, I was not able to scroll up to see all of the words 
// in the terminal. It also reduced the run time greatly.




#include <iostream>
#include <vector>
#include <regex>
#include <map>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "RBT.hpp"
#include "RBTPrint.hpp"
#include "ST.hpp"

int main() {

    // get starting time value
    const auto start = std::chrono::high_resolution_clock::now();

    // parse input text
    std::string text;
    std::vector<std::string> tokens;
    const std::regex delim("\\s+"); 
    while (std::cin >> text) {
        auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
        auto end = std::sregex_token_iterator();
        for (std::sregex_token_iterator word = begin; word != end; word++) {
            tokens.push_back(*word);
        }
    }

    //create .txt file for output
    std::ofstream output_file("output.txt");
    if (!output_file.is_open()) {
        std::cout << "Error: could not open text output file correctly" << std::endl;
        return 1;
    }

    // if word doesn't exist in table, inserts it with count 1
    // if word does exist, increment count by 1
    ST<std::string, int> WordTable;
    for (const auto & str : tokens) {
        auto temp = WordTable.find(str);
        if (temp == nullptr) {
            WordTable.insert(str, 1);
        } else {
            (temp->value) ++;
        }
    }

    // put WordTable to vector
    std::vector<std::pair<std::string, int>> WordTableVector;
    WordTableVector = WordTable.toVector();

    // stable sort vector based on values to preserve alphabetic ordering
    std::stable_sort(WordTableVector.begin(), WordTableVector.end(),[=](const std::pair<std::string, int> &val1, const std::pair<std::string, int> &val2) {
        return val1.second > val2.second;
    });

    // output sorted vector to text file, then close output file
    output_file << "The input file contains " << WordTable.size() << " unique words." << std::endl;
    for (const auto &wordPair : WordTableVector) {
        output_file << wordPair.first << ": " << wordPair.second << std::endl;
    }
    output_file.close();

    // get ending time value, calculate duration, print duration
    const auto stop = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
    std::cout << milliseconds.count() << " milliseconds elapsed." << std::endl;

    return 0;
}
