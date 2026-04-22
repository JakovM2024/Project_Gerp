//this file is the wrapper for the case insensitive and case sensetive maps
#ifndef HASH_H
#define HASH_H
#include <string>

class Maps{
    public:

    //query loop

    struct WordInstance{
        std::string word = ""; // need to store the actual word so we can tell 
                            //wether to probe or append to list 
        int file = -1; //outIndex for files vector
        int stringLine = -1; //innerIndex for string line 2d vector
    };

    private:

    //processing a word based on query, inSense or sense    //reference to caseInsense and caseSense maps
    

};

#endif