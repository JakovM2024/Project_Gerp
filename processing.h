/*
 *   processing.h
 *   Marcus Ho and Jakov Maronhic
 *   2026-04-24
 *   CS 15 Project 4: gerp
 *
 *   Interface for the DirectoryProcessor class, which walks a directory
 *   tree to collect every file path and strips leading and trailing
 *   non-alphanumeric characters from a token.
 */

#ifndef __PROCESSING_H
#define __PROCESSING_H

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