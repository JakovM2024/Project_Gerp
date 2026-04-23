#ifndef CASE_INSENSITIVE_H
#define CASE_INSENSITIVE_H

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include <list> 

class hashMap{
    public:

    //using linear probing not chaining
    hashMap();
    ~hashMap();
    //insert function
    struct WordInstance{
        std::string word = ""; // need to store the actual word so we can tell 
                            //wether to probe or append to list 
        int file = -1; //outIndex for files vector
        int stringLine = -1; //innerIndex for string line 2d vector
    };
    
    void insert(std::string &word, hashMap::WordInstance location);
    std::vector<hashMap::WordInstance> lookup(std::string &word);
    void resize(); 

    //maybe we just void return and print to file or cout to save space

    private:

    int array_size;
    int num_entries; 
    const float max_load_factor = 0.7;

    std::vector<WordInstance> *arr; //the array that holds a list of 
            //wordInstances at each index(everylocation that word appears)

    int hashfunc(std::string key);


    //collison handler
    //calculate load factor
    //resize
    //nessecary methods and members 


};

#endif 