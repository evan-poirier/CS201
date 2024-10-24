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

    // //create .txt file for output
    // std::ofstream output_file("output.txt");
    // if (!output_file.is_open()) {
    //     std::cout << "Error: could not open text output file correctly" << std::endl;
    //     return 1;
    // }

    // insert descriptive comment
    ST<std::string, int> WordTable;
    for (const auto & str : tokens) {
        auto temp = WordTable.find(str);
        if (temp == nullptr) {
            WordTable.insert(str, 1);
        } else {
            (temp->value) ++;
        }
    }

    WordTable.display();

    //    for (const auto & str : tokens) {
    //       auto it = wordOccurrences.find(str);

    //       if (it != wordOccurrences.end()) {
    //          it->second ++;
    //       } else {
    //          wordOccurrences.insert(std::pair<std::string, int>(str, 1));
    //       }
    //    }

    // fills a vector with all of the pairs from the map in O(n) time
    // also creates a count of total and unique words in the output file
    //    std::vector<std::pair<std::string, int>> wordsVector;
    //    int total_words = 0;
    //    int unique_words = 0;

    //    for (const auto &wordPair : wordOccurrences) {
    //       total_words += wordPair.second;
    //       unique_words ++;
    //       wordsVector.push_back(wordPair);
    //    }

    //    output_file << "The input file contains " << unique_words << " unique words, and " << total_words << " total words:" << std::endl << std::endl;

    //    // sorts the vector by the value of each pair (number of appearances) using std::stable_sort in O(n lg(n)) time
    //    std::sort(wordsVector.begin(), wordsVector.end(), [=](std::pair<std::string, int> &x, std::pair<std::string, int> &y) {

    //       // I forgot to put this bit of code in initially:
    //       if (x.second == y.second) {
    //          return x.first > y.first;
    //       }
    //       // end of new code

    //       return x.second > y.second;
    //    });

    //    // puts output into text file, close file
    //    for (const auto &wordPair : wordsVector) {
    //       output_file << wordPair.first << ": " << wordPair.second << std::endl;
    //    }
    //    output_file.close();

    // get ending time value, calculate duration, print duration
    const auto stop = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
    std::cout << milliseconds.count() << " milliseconds elapsed." << std::endl;

    return 0;
}
