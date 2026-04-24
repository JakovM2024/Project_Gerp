/*
 *   wrapper.h
 *   Marcus Ho and Jakov Maronhic
 *   2026-04-24
 *   CS 15 Project 4: gerp
 *
 *   Interface for the Wrapper class, which owns both the case-sensitive
 *   and case-insensitive hash maps along with the filepaths and lines
 *   data. Declares the constructor that builds the index from a
 *   directory and the public search method used by the query loop.
 */

#ifndef HASH_H
#define HASH_H
#include <string>
#include "hashMap.h"
#include <vector>
#include "processing.h"
#include <fstream>

class Wrapper{
    public:

    Wrapper(std::string dir);
    ~Wrapper();

    void search(bool case_sense, std::string query, std::ofstream &outfile);

    private:


    std::string directory;
    hashMap sensitive;
    hashMap insensitive;
    DirectoryProcessor processor;
    void indexFilePaths();
    void readAndIndexLines();


    std::vector<std::string> filepaths;
    std::vector<std::vector<std::string>> lines;

};

#endif