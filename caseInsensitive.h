#ifndef CASE_INSENSITIVE_H
#define CASE_INSENSITIVE_H

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include "hash.h"
#include <list>

class caseInsense{
    public:

    //using linear probing not chaining
    caseInsense();
    ~caseInsense();
    //insert function
    void insert(std::string word, Maps::WordInstance location);
    std::list<Maps::WordInstance> lookup(std::string word);
    //maybe we just void return and print to file or cout to save space

    private:

    int array_size;
    float load_factor;

    std::list<Maps::WordInstance> *arr; //the array that holds a list of 
            //wordInstances at each index(everylocation that word appears)

    int hashfunc(std::string key);

    //collison handler
    //calculate load factor
    //resize
    //nessecary methods and members 


};

#endif 