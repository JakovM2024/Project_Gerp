#ifndef CASE_INSENSITIVE_H
#define CASE_INSENSITIVE_H

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include "hash.h"

class caseInsense{
    public:

    caseInsense();
    //insert function
    void insert(std::string word, Maps::WordInstance location);
    Maps::WordInstance lookup(std::string word); //maybe we can use pair to 
    //pull out the strings of the two indecies

    private:

    int array_size;
    int load_factor;

    Maps::WordInstance *arr;

    //collison handler
    //calculate load factor
    //resize
    //nessecary methods and members 


};

#endif 