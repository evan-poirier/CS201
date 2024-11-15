/*
Name: Evan Poirier
Email: espoirier@crimson.ua.edu
Course Section: Fall 2024 CS201
Homework #: 3
*/

#ifndef _MOVIE_HPP_
#define _MOVIE_HPP_

#include <string>
#include <list>

class Movie {
private:
    std::string title;
    std::list<std::string> actors;

public:
    // this is used to create a temporary movie object that can then be searched for in a set
    Movie(std::string title) {
        this->title = title;
    }

    Movie(std::string title, std::list<std::string> actors) {
        this->title = title;
        this->actors = actors;
    }

    // defines ordering so that movies are sorted alphabetically by title
    bool operator<(const Movie& other) const {
        return title < other.title;
    }

    bool ContainsActor(std::string actor) const {
        for (auto actorIterator = this->actors.begin(); actorIterator != this->actors.end(); ++actorIterator) {
    	    if (*actorIterator == actor) {
                return true;
            }
	    }
        return false;
    }

    std::string GetActorsList() const {
        std::string list;
        
        for (auto actorIterator = this->actors.begin(); actorIterator != this->actors.end(); ++actorIterator) {
            list.append("\n");
            list.append(*actorIterator);
	    }

        return list;
    }

    std::string GetTitle() const {
        return this->title;
    }
};

class MovieDatabase {
private:
    std::set<Movie> movies;

    // return the list of actors appearing in a movie
    std::string GetMovie(std::string query) {
        std::string output;

        Movie temp(query);
        auto it = movies.find(temp);

        if (it != movies.end()) {
            output.append(it->GetActorsList());
        } else {
            output.append("\n");
            output.append("The movie could not be found.");
        }

        return output;
    }

    // returns the list of movies that a given actor has been in
    std::string GetOeuvre(std::string query) {
        std::string output;
        bool workFound = false;

        for (auto it = this->movies.begin(); it != this->movies.end(); ++it) {
            if (it->ContainsActor(query)) {
                workFound = true;
                output.append("\n");
                output.append(it->GetTitle());
            }
	    }

        // if an actor doesn't appear in the database, print an appropriate message
        if (!workFound) {
            output.append("\n");
            output.append("No films found for this actor.");
        }

        return output;
    }

public:
    // use std::set functionality to add a new movie object
    void AddMovie(Movie movieToAdd) {
        this->movies.insert(movieToAdd);
    }

    // determine if a query is for a movie or an actor, then return appropriate results
    std::string Search(std::string query) {
        std::string output;

        // if the query contains a parenthesis, it is a title, otherwise it is the name of an actor
        if (query.find('(') != std::string::npos) {
            output.append("Actors appearing in '");
            output.append(query);
            output.append("':");
            output.append(this->GetMovie(query));
        } else {
            output.append("Films featuring '");
            output.append(query);
            output.append("':");
            output.append(this->GetOeuvre(query));
        }
        
        output.append("\n");

        return output;
    }
};

#endif