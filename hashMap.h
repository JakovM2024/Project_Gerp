#ifndef CASE_INSENSITIVE_H
#define CASE_INSENSITIVE_H

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include "wrapper.h"
#include <vector>
#include <list> 

class hashMap{
    public:

    //using linear probing not chaining
    hashMap();
    ~hashMap();
    //insert function
    void insert(std::string &word, Wrapper::WordInstance location);
    std::vector<Wrapper::WordInstance> lookup(std::string &word);
    void resize(); 

    //maybe we just void return and print to file or cout to save space

    private:

    int array_size;
    int num_entries; 
    const float max_load_factor = 0.7;

    std::vector<Wrapper::WordInstance> *arr; //the array that holds a list of 
            //wordInstances at each index(everylocation that word appears)

    int hashfunc(std::string key);

    //collison handler
    //calculate load factor
    //resize
    //nessecary methods and members 


};

#endif 