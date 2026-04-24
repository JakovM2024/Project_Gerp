/*
 *   processing.cpp
 *   Marcus Ho and Jakov Maronhic
 *   2026-04-24
 *   CS 15 Project 4: gerp
 *
 *   Implements the DirectoryProcessor class, which walks an FSTree to
 *   collect every file path under a given directory and strips leading
 *   and trailing non-alphanumeric characters from a token.
 */

#include <string>
#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"
#include <iostream>

using namespace std;

/*
 * name: traverseDirectory()
 * purpose: Walks the directory tree rooted at the given directory and
 *          collects the full path of every file inside it
 * arguments: the root directory name and a reference to the filepaths
 *            vector to fill
 * returns: none
 * effects: Pushes every file path into filepaths
 */
void DirectoryProcessor::traverseDirectory(string directory,
                                        std::vector<std::string> &filepaths){
    FSTree files(directory);
    DirNode *rootfile = files.getRoot();

    string startPath = "";
    traverseHelper(startPath, rootfile, filepaths);
}

/*
 * name: traverseHelper()
 * purpose: Recursive helper that visits the current DirNode, records any
 *          files it contains, and then recurses into each subdirectory
 * arguments: the path accumulated so far, a pointer to the current
 *            DirNode, and a reference to the filepaths vector to fill
 * returns: none
 * effects: Appends each discovered file's full path into filepaths
 */
void DirectoryProcessor::traverseHelper(string path, DirNode *currFile,
                                        std::vector<std::string> &filepaths){
    if (currFile->isEmpty()){
        return;
    }
    path += currFile->getName() + "/";
    if (currFile->hasFiles()){
        int numFiles = currFile->numFiles();
        for (int i = 0; i < numFiles; i++){
            //cout << path + currFile->getFile(i) << endl;
            filepaths.push_back(path + currFile->getFile(i));
        }
    }
    if (currFile->hasSubDir()){
        int numSubDirs = currFile->numSubDirs();
        for (int i = 0; i < numSubDirs; i++){
            traverseHelper(path, currFile->getSubDir(i), filepaths);
        }
        return;
    }
}

/*
 * name: stripNonAlphaNum()
 * purpose: Removes leading and trailing non-alphanumeric characters from
 *          a token, keeping everything between the first and last
 *          alphanumeric characters
 * arguments: the input string
 * returns: the stripped string (empty if no alphanumeric characters
 *          were present)
 * effects: none
 */
string DirectoryProcessor::stripNonAlphaNum(string input) {
    string strippedString; 
    int startPos = -1; 
    int endPos = -1;

    //!!!Hello!!!!
    for (size_t i = 0; i < input.length(); i++) { 
        if (isalnum(input[i]) != 0) {
            startPos = i; 
            break; 
        }
    }

    for (int j = input.length() - 1; j >= 0; j--) {
        if (isalnum(input[j]) != 0) {
            endPos = j; 
            break;
        }
    }

    if (startPos == -1 and endPos == -1) {
        return ""; 
    }

    int stringLen = (endPos - startPos) + 1; 
    strippedString = input.substr(startPos, stringLen); 

    return strippedString;
}