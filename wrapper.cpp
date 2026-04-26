/*
 *   wrapper.cpp
 *   Marcus Ho and Jakov Maronhic
 *   2026-04-24
 *   CS 15 Project 4: gerp
 *
 *   Implements the Wrapper class, which ties the directory traversal,
 *   file reading, and both hash maps together. It builds the full index
 *   on construction and runs case-sensitive or case-insensitive queries,
 *   writing their results to the output file.
 */

#include <string>
#include "wrapper.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

/*
 * name: Wrapper()
 * purpose: Builds the full index by traversing the given directory tree
 *          and recording every word occurrence in both the sensitive and
 *          insensitive hash maps
 * arguments: the root directory name (string) to index
 * returns: none
 * effects: Populates filepaths, lines, sensitive, and insensitive
 */
Wrapper::Wrapper(string dir){
    directory = dir;
    indexFilePaths();
    readAndIndexLines();
}

/*
 * name: ~Wrapper()
 * purpose: Destroys the Wrapper
 * arguments: none
 * returns: none
 * effects: Member destructors handle cleanup automatically
 */
Wrapper::~Wrapper() {}

/*
 * name: indexFilePaths()
 * purpose: Walks the directory tree and collects every file path into
 *          the filepaths vector
 * arguments: none
 * returns: none
 * effects: Fills filepaths via the DirectoryProcessor
 */
void Wrapper::indexFilePaths(){

    processor.traverseDirectory(this->directory, filepaths);
}

/*
 * name: readAndIndexLines()
 * purpose: Opens every indexed file, stores each raw line, and inserts
 *          every word occurrence into both hash maps (the raw token goes
 *          into the sensitive map, the lowercased token into the
 *          insensitive map)
 * arguments: none
 * returns: none
 * effects: Populates lines and both hash maps with word occurrences
 */
void Wrapper::readAndIndexLines(){
    for (size_t i = 0; i < filepaths.size(); i++){
        ifstream infile(filepaths.at(i));
        if(not infile.is_open()) continue;

        //logic for reading lines into the file
        string line = "";
        int j = 0;

        //line 28 would throw range error if there was no vector
        lines.push_back(vector<string>());
        while(getline(infile, line)){
            lines.at(i).push_back(line);
            stringstream ss(line);
            std::string word;

            //chooses which map to insert to
            while (ss >> word) {
                word = processor.stripNonAlphaNum(word);
                if (word.empty()) continue;
                sensitive.insert(word, i, j);
                for (size_t k = 0; k < word.size(); k++){
                    word[k] = tolower((unsigned char)word[k]);
                }
                insensitive.insert(word, i, j);
            }
            j++;
        }
    }
}

/*
 * name: search()
 * purpose: Runs a query (one or more whitespace-separated words) against
 *          either the sensitive or insensitive hash map and writes the
 *          results to the output file in the required format
 * arguments: case_sense (true for case-sensitive search, false for
 *            insensitive), the query string, and the output file stream
 * returns: none
 * effects: Writes either matching "path:lineNumber: lineText" lines or a
 *          "Not Found" message to outfile for each word in the query
 */
void Wrapper::search(bool case_sense, string query, std::ofstream &outfile){
    vector<hashMap::WordInstance> results;
    stringstream ss(query);
    std::string word;
    while (ss >> word) {
        word = processor.stripNonAlphaNum(word);
        string stripped = word;
        //choose which map to use and push
        if (not word.empty()){
            if (case_sense){
                results = sensitive.lookup(word);
            } else {
                for (size_t k = 0; k < word.size(); k++){
                    word[k] = tolower((unsigned char)word[k]);
                }
                results = insensitive.lookup(word);
            }
            //print the info using the index vectors
            for (size_t i = 0; i < results.size(); i++){
                string filepath = filepaths.at(results.at(i).file);
                string line = lines.at(results.at(i).file)
                                   .at(results.at(i).stringLine);
                outfile << filepath + ":" +
                    to_string(results.at(i).stringLine + 1) + ": " + line
                    << endl;
            }
        }

        if (results.empty() or word.empty()) {
            if (case_sense) {
                outfile << stripped
                        << " Not Found. Try with @insensitive or @i."
                        << endl;
            } else {
                outfile << stripped << " Not Found." << endl;
            }
        }

    }
}