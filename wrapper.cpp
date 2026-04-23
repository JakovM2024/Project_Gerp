
#include <string>
#include "wrapper.h"
#include <vector>
#include <fstream>
using namespace std;

Wrapper::Wrapper(string dir){
    directory = dir;
}

void Wrapper::indexFilePaths(){

    processor.traverseDirectory(this->directory, filepaths);
}

void Wrapper::readAndIndexLines(){
    for (int i = 0; i < filepaths.size(); i++){
        ifstream infile(filepaths.at(i));
        //logic for reading lines into the file
        string line = "";
        int j = 0;
        while(getline(infile, line)){
            lines.at(i).push_back(line);
            //hash words
            j++;
        }
    }
}