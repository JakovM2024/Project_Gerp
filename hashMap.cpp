#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include "hashMap.h"
#include "wrapper.h"
using namespace std;

caseInsense::caseInsense(){
    array_size = 20;
    load_factor = 0;
    arr = new list<Wrapper::WordInstance> [array_size];
}

caseInsense::~caseInsense(){
    delete arr;
}

int caseInsense::hashfunc(string key) {
    size_t h = hash<string>{}(key);
    return h % array_size;
}

void caseInsense::insert(string word, Wrapper::WordInstance location){
    int index = hashfunc(word);
    
}