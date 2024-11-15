/*
Name: Evan Poirier
Email: espoirier@crimson.ua.edu
Course Section: Fall 2024 CS201
Homework #: 3
*/

/*
This program operates based off of the assumption that queries containing parentheses are movies,
and all other queries are actors.
*/

/*
Sample program that reads a "/" delimited file and a query file and prints the parsed concents to a .txt file.
To Compile: g++ -std=c++20 HW3Sample.cpp
To Run: ./a.out dbfile1.txt query.txt
*/

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <set>

#include "Movie.hpp"

int main(int argc, char *argv[]) {
	// Open output file
	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open()) {
		std::cout << "Error opening output file." << std::endl;
		return 1;
	}

	// Open and verify database file
	if (argc != 3) {
	   std::cout << "Usage: " << argv[0] << " <db file> <query file>" << std::endl;
	   std::exit(-1);
	}

	std::string line, name;
	std::regex delim("/");
	std::ifstream dbfile(argv[1]);
	if (!dbfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[1] << std::endl;
	   std::exit(-1);
	}

	// Create a container for the movies
	MovieDatabase movies;

	// Iterate through each movie and its actors
	while (std::getline(dbfile, line)) {
		auto begin = std::sregex_token_iterator(line.begin(), line.end(), delim, -1);
		auto end = std::sregex_token_iterator();

		// store the title for the movie
		std::string currTitle = *begin;
		++begin;

		// store a list of actors for the movie
		std::list<std::string> currActorList;
		for (std::sregex_token_iterator word = begin; word != end; ++word) {
			currActorList.push_back(*word);
		}

		// create movie object with title and actors, and add it to the container
		Movie currMovie(currTitle, currActorList);
		movies.AddMovie(currMovie);
	}

	dbfile.close();

	// open query file
	std::ifstream queryfile(argv[2]);
	if (!queryfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[2] << std::endl;
	   std::exit(-1);
	}

	// perform queries using search member function
	while (std::getline(queryfile, name)) {
	   outputFile << movies.Search(name) << std::endl;
	}

	queryfile.close();

	return 0;
}

