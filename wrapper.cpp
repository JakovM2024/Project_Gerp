
#include <string>
#include "wrapper.h"
#include <vector>
#include <fstream>
#include <sstream>
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
        lines.push_back(vector<string>());
        //logic for reading lines into the file
        string line = "";
        int j = 0;
        while(getline(infile, line)){
            lines.at(i).push_back(line);
            stringstream ss(line);
            std::string word;
            while (ss >> word) {
                word = processor.stripNonAlphaNum(word);
                if (word.empty()) continue;
                sensitive.insert(word, i, j);
                for (int k = 0; k < word.size(); k++){
                    word[k] = tolower((unsigned char)word[k]);
                }
                insensitive.insert(word, i, j);
            }
            j++;
        }
    }
}

void Wrapper::search(bool case_sense, string query, std::ofstream &outfile){
    //need to fix if query is multiple words
    vector<hashMap::WordInstance> results;
    stringstream ss(query);
    std::string word;
    while (ss >> word) {
        word = processor.stripNonAlphaNum(word);
        if (word.empty()) continue;
        if (case_sense){
            results = sensitive.lookup(word);
        } else {
            for (int k = 0; k < word.size(); k++){
                word[k] = tolower((unsigned char)word[k]);
            }
            results = insensitive.lookup(word);
        }
        for (int i = 0; i < results.size(); i++){
            string filepath = filepaths.at(results.at(i).file);
            string line = lines.at(results.at(i).file).at(results.at(i).stringLine);
            outfile << filepath + ":" + to_string(results.at(i).stringLine + 1) +
                ":" + line << endl;
        }

        if (results.empty()) {
            outfile << word << " Not Found" << endl;
        }
    }
}