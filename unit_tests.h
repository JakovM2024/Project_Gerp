/*
 * unit_tests.h
 * Jakov Marohnic and Marcus Ho
 * 04/24/2026
 *
 * CS15 Proj 4: gerp
 *
 * Unit tests for the hashMap and DirectoryProcessor classes. Tests cover
 * basic insert and lookup, duplicate prevention, resize correctness,
 * missing word lookup, and stripping of non-alphanumeric characters.
 *
 */

#include <string>
#include "processing.h"
#include "hashMap.h"
#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <cassert>
using namespace std;


//DirectoryProcessor tests 


//empty string input returns empty string
void stripEmpty(){
    string input = "";
    DirectoryProcessor processor;
    string output = processor.stripNonAlphaNum(input);
    assert(output == "");
}

//already clean words are returned unchanged
void stripAlrStripped(){
    string input1 = "hello";
    string input2 = "HELLO";
    DirectoryProcessor processor;
    string output1 = processor.stripNonAlphaNum(input1);
    string output2 = processor.stripNonAlphaNum(input2);
    assert(output1 == input1);
    assert(input2 == output2);
}

//leading and trailing non-alphanumeric characters are stripped
void stripNonAplhaNum(){
    string input1 = "';]1234Co-]mp(&*)";
    DirectoryProcessor processor;
    string output1 = processor.stripNonAlphaNum(input1);
    assert(output1 == "1234Co-]mp");
}

//all non-alphanum string, should return empty
void stripAllSpecial(){
    DirectoryProcessor processor;
    assert(processor.stripNonAlphaNum("!!!---!!!") == "");
    assert(processor.stripNonAlphaNum("...") == "");
}

//single alphanum character
void stripSingleChar(){
    DirectoryProcessor processor;
    assert(processor.stripNonAlphaNum("a") == "a");
    assert(processor.stripNonAlphaNum("!a!") == "a");
    assert(processor.stripNonAlphaNum("5") == "5");
}

//non-alphanum in the middle should be preserved
void stripMiddlePreserved(){
    DirectoryProcessor processor;
    assert(processor.stripNonAlphaNum("he-llo") == "he-llo");
    assert(processor.stripNonAlphaNum("!!he-llo!!") == "he-llo");
}

//numbers mixed with symbols
void stripNumbers(){
    DirectoryProcessor processor;
    assert(processor.stripNonAlphaNum("***42***") == "42");
    assert(processor.stripNonAlphaNum("3.14") == "3.14");
}


//hashMap tests

//lookup on empty map returns empty vector
void hashMapLookupEmpty(){
    hashMap map;
    string word = "hello";
    vector<hashMap::WordInstance> result = map.lookup(word);
    assert(result.empty());
}

//basic insert and lookup
void hashMapInsertAndLookup(){
    hashMap map;
    string word = "hello";
    map.insert(word, 0, 5);
    vector<hashMap::WordInstance> result = map.lookup(word);
    assert(result.size() == 1);
    assert(result[0].word == "hello");
    assert(result[0].file == 0);
    assert(result[0].stringLine == 5);
}

//inserting same word at different locations accumulates entries
void hashMapMultipleLocations(){
    hashMap map;
    string word = "hello";
    map.insert(word, 0, 1);
    map.insert(word, 1, 3);
    map.insert(word, 2, 7);
    vector<hashMap::WordInstance> result = map.lookup(word);
    assert(result.size() == 3);
}

//duplicate (same word, same file, same line) should not be inserted twice
void hashMapNoDuplicates(){
    hashMap map;
    string word = "hello";
    map.insert(word, 0, 1);
    map.insert(word, 0, 1);
    vector<hashMap::WordInstance> result = map.lookup(word);
    assert(result.size() == 1);
}

//different words should be stored independently
void hashMapDifferentWords(){
    hashMap map;
    string w1 = "hello";
    string w2 = "world";
    map.insert(w1, 0, 0);
    map.insert(w2, 0, 1);
    assert(map.lookup(w1).size() == 1);
    assert(map.lookup(w2).size() == 1);
    assert(map.lookup(w1)[0].stringLine == 0);
    assert(map.lookup(w2)[0].stringLine == 1);
}

//insert enough words to trigger a resize
void hashMapResize(){
    hashMap map;
    //default array_size is 20, load factor 0.7 -> triggers at 14 entries
    string words[] = {"a","b","c","d","e","f","g","h","i","j",
                      "k","l","m","n","o"};
    for (int i = 0; i < 15; i++){
        map.insert(words[i], 0, i);
    }
    //all words should still be findable after resize
    for (int i = 0; i < 15; i++){
        vector<hashMap::WordInstance> result = map.lookup(words[i]);
        assert(result.size() == 1);
        assert(result[0].stringLine == i);
    }
}

//lookup word that was never inserted returns empty
void hashMapLookupMissing(){
    hashMap map;
    string w = "cat";
    string w2 = "dog";
    map.insert(w, 0, 0);
    vector<hashMap::WordInstance> result = map.lookup(w2);
    assert(result.empty());
}