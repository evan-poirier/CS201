// Sample program that reads a "/" delimited file and a query file and 
// prints the parsed concents to stdout
// To Compile: g++ -std=c++20 HW3Sample.cpp
// To Run: ./a.out dbfile1.txt query.txt

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main(int argc, char *argv[]) {
	int i = 0;
	// check for correct command-line arguments
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

	std::cout << "***Reading db file " << argv[1] << "***" << std::endl;
	while (std::getline(dbfile, line)) {
	   // parse each line for tokens delimited by "/"
	   auto begin = std::sregex_token_iterator(line.begin(), line.end(), delim, -1);
	   auto end = std::sregex_token_iterator();
	   std::cout << "***Line " << ++i << " ***" << std::endl;
	   std::cout << "Movie:\t" << *begin << std::endl;
	   ++begin;
	   std::cout << "Actors: " << std::endl;
	   for (std::sregex_token_iterator word = begin; word != end; ++word) {
		std::cout << "\t" << *word << std::endl;
	   }
	}
	dbfile.close();
	std::cout << "***Done reading db file " << argv[1] << "***" << std::endl;

	std::ifstream queryfile(argv[2]);
	if (!queryfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[2] << std::endl;
	   std::exit(-1);
	}

	std::cout << "***Reading query file " << argv[2] << "***" << std::endl;
	while (std::getline(queryfile, name)) {
	   std::cout << name << std::endl;
	}
	queryfile.close();
	std::cout << "***Done reading query file " << argv[2] << "***" << std::endl;

	return 0;
}

