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
/*
string DirectoryProcessor::stripNonAlphaNum(string input){
    string prossecedString = "";
    bool finished = false;
    int start = 0;
    int end = input.length() - 1;
    while (not finished){
        if ( (47 < input[start] and input[start] < 58) and )
    }
}
    */