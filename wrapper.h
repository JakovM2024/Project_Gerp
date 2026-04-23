//this file is the wrapper for the case insensitive and case sensetive maps
#ifndef HASH_H
#define HASH_H
#include <string>
#include "hashMap.h"
#include <vector>
#include "processing.h"

class Wrapper{
    public:

    

    void indexFilePaths(DirectoryProcessor &processor, 
                        std::vector<std::string> filepaths);

    // method for reading files and adding words to hash
    //query loop method

    private:

    hashMap sensitive;
    hashMap insensitive;
    DirectoryProcessor processor;


    std::vector<std::string> filepaths;
    std::vector<std::vector<std::string>> lines;

    //processing a word based on query, inSense or sense    //reference to caseInsense and caseSense maps
    

};

#endif