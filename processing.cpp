#include <string>
#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"
#include <iostream>

using namespace std;

void DirectoryProcessor::traverseDirectory(string directory){
    FSTree files(directory);
    DirNode *rootfile = files.getRoot();

    string startPath = "";
    traverseHelper(startPath, rootfile);
}

void DirectoryProcessor::traverseHelper(string path, DirNode *currFile){
    if (currFile->isEmpty()){
        return;
    }
    path += currFile->getName() + "/";
    if (currFile->hasFiles()){
        int numFiles = currFile->numFiles();
        for (int i = 0; i < numFiles; i++){
            cout << path + currFile->getFile(i) << endl;
        }
    }
    if (currFile->hasSubDir()){
        int numSubDirs = currFile->numSubDirs();
        for (int i = 0; i < numSubDirs; i++){
            currFile = currFile->getSubDir(i);
            traverseHelper(path, currFile);
        }
        return;
    }
}

string DirectoryProcessor::stripNonAlphaNum(string input) {
    string strippedString; 
    int startPos = -1; 
    int endPos = -1;

    //!!!Hello!!!!
    for (int i = 0; i < input.length(); i++) { 
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

    if (startPos == -1 && endPos == -1) {
        return ""; 
    }

    int stringLen = (endPos - startPos) + 1; 
    strippedString = input.substr(startPos, stringLen); 

    return strippedString;
}