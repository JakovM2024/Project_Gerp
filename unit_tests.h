#include <string>
#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <cassert>
using namespace std;


void stripEmpty(){
    string input = "";
    DirectoryProcessor processor;
    string output = processor.stripNonAlphaNum(input);
    assert(output == "");
}

void stripAlrStripped(){
    string input1 = "hello";
    string input2 = "HELLO";
    DirectoryProcessor processor;
    string output1 = processor.stripNonAlphaNum(input1);
    string output2 = processor.stripNonAlphaNum(input2);
    assert(output1 == input1);
    assert(input2 == output2);
}

void stripNonAplhaNum(){
    string input1 = "';]1234Co-]mp(&*)";
    DirectoryProcessor processor;
    string output1 = processor.stripNonAlphaNum(input1);
    assert(output1 == "1234Co-]mp");
}