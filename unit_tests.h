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


// Additional DirectoryProcessor tests 

//leading and trailing whitespace should be stripped (space is not alnum)
void stripWhitespace(){
    DirectoryProcessor processor;
    assert(processor.stripNonAlphaNum("  hello  ") == "hello");
    assert(processor.stripNonAlphaNum("\thello\t") == "hello");
}

//single non-alphanumeric character should return empty
void stripSingleNonAlnum(){
    DirectoryProcessor processor;
    assert(processor.stripNonAlphaNum("!") == "");
    assert(processor.stripNonAlphaNum(".") == "");
}

//mixed case should be preserved exactly
void stripPreservesCase(){
    DirectoryProcessor processor;
    assert(processor.stripNonAlphaNum("HeLLo") == "HeLLo");
    assert(processor.stripNonAlphaNum("!!CamelCase!!") == "CamelCase");
}


//--- Additional hashMap tests ---

//map should be case sensitive: "Hello" and "hello" are different keys
void hashMapCaseSensitive(){
    hashMap map;
    string upper = "Hello";
    string lower = "hello";
    map.insert(upper, 0, 0);
    map.insert(lower, 0, 1);
    vector<hashMap::WordInstance> upResult = map.lookup(upper);
    vector<hashMap::WordInstance> lowResult = map.lookup(lower);
    assert(upResult.size() == 1);
    assert(lowResult.size() == 1);
    assert(upResult[0].word == "Hello");
    assert(lowResult[0].word == "hello");
}

//same word, same file, different line should be stored as separate entries
void hashMapSameFileDiffLine(){
    hashMap map;
    string w = "hello";
    map.insert(w, 0, 1);
    map.insert(w, 0, 2);
    map.insert(w, 0, 3);
    vector<hashMap::WordInstance> result = map.lookup(w);
    assert(result.size() == 3);
}

//same word, different file, same line should be stored as separate entries
void hashMapDiffFileSameLine(){
    hashMap map;
    string w = "hello";
    map.insert(w, 0, 5);
    map.insert(w, 1, 5);
    map.insert(w, 2, 5);
    vector<hashMap::WordInstance> result = map.lookup(w);
    assert(result.size() == 3);
}

//two different words that may collide in the same bucket should both
//be independently retrievable
void hashMapHashCollision(){
    hashMap map;
    //insert many distinct keys so most buckets have multiple residents
    string keys[] = {"alpha","beta","gamma","delta","epsilon","zeta",
                     "eta","theta","iota","kappa","lambda","mu",
                     "nu","xi","omicron","pi","rho","sigma","tau",
                     "upsilon","phi","chi","psi","omega"};
    int n = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < n; i++){
        map.insert(keys[i], i, i);
    }
    //every key still uniquely retrievable
    for (int i = 0; i < n; i++){
        vector<hashMap::WordInstance> result = map.lookup(keys[i]);
        assert(result.size() == 1);
        assert(result[0].word == keys[i]);
        assert(result[0].file == i);
        assert(result[0].stringLine == i);
    }
}

//insert many words to trigger multiple resizes
void hashMapStressResize(){
    hashMap map;
    const int N = 500;
    vector<string> words;
    for (int i = 0; i < N; i++){
        words.push_back("word" + to_string(i));
    }
    for (int i = 0; i < N; i++){
        map.insert(words[i], i % 10, i);
    }
    //all entries still findable after multiple resizes
    for (int i = 0; i < N; i++){
        vector<hashMap::WordInstance> result = map.lookup(words[i]);
        assert(result.size() == 1);
        assert(result[0].file == i % 10);
        assert(result[0].stringLine == i);
    }
}

//dedup must still work correctly after a resize has occurred
void hashMapDedupAfterResize(){
    hashMap map;
    string w = "repeat";
    //insert enough other entries to trigger at least one resize first
    vector<string> filler;
    for (int i = 0; i < 30; i++){
        filler.push_back("filler" + to_string(i));
    }
    for (int i = 0; i < 30; i++){
        map.insert(filler[i], 0, i);
    }
    //now hammer the same (word, file, line) and confirm only one entry
    for (int i = 0; i < 50; i++){
        map.insert(w, 9, 9);
    }
    vector<hashMap::WordInstance> result = map.lookup(w);
    assert(result.size() == 1);
    assert(result[0].file == 9);
    assert(result[0].stringLine == 9);
}