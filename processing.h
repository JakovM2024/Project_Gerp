#ifndef __PROCESSING_H
#define __PROCESSING_H

/*
*    Update file header if you use this file in your solution to phase 2 
*/

#include <string>
#include "DirNode.h"
using namespace std;
class DirectoryProcessor{

    public:
        string stripNonAlphaNum(string input);
        void traverseDirectory(string directory, 
                               std::vector<std::string> &filepaths);

    private:

        void traverseHelper(string path, DirNode *currFile,
                            std::vector<std::string> &filepaths);
};

#endif 