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
    arr = new vector<Wrapper::WordInstance> [array_size];
}

caseInsense::~caseInsense(){
    delete[] arr;
}

int caseInsense::hashfunc(string key) {
    size_t h = hash<string>{}(key);
    return h % array_size;
}

void caseInsense::insert(string word, Wrapper::WordInstance location){
    //compare load factor and expand if needed

    int index = hashfunc(word);
    while ((not arr[index].empty()) and 
        (arr[index].at(0).word != location.word)){
        index = (index + 1) % array_size;
    }
    arr[index].push_back(location);
}

