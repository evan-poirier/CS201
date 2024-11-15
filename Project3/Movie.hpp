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
    Movie(std::string title, std::list<std::string> actors) {
        this->title = title;
        this->actors = actors;
    }
    //~Movie();   

    bool operator<(const Movie& other) const {
        return title < other.title;
    }

    bool ContainsActor(std::string actor);

    std::string GetActorsList() const {
        std::string list;
        
        list = "this is a placeholder";

        return list;
    }

    std::string GetTitle() const {
        return this->title;
    }
};

#endif