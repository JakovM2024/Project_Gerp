#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include "hash.h"
#include "caseInsensitive.h"
using namespace std;

caseInsense::caseInsense(){
    array_size = 20;
    load_factor = 0;
    arr = new list<Maps::WordInstance> [array_size];
}

caseInsense::~caseInsense(){
    delete arr;
}

int caseInsense::hashfunc(string key) {
    size_t h = hash<string>{}(key);
    return h % array_size;
}

void caseInsense::insert(string word, Maps::WordInstance location){
    int index = hashfunc(word);
    
}