#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include "hashMap.h"
#include "wrapper.h"
using namespace std;

hashMap::hashMap(){
    array_size = 20;
    num_entries = 0; 
    arr = new vector<Wrapper::WordInstance> [array_size];
}

hashMap::~hashMap(){
    delete[] arr;
}

int hashMap::hashfunc(string key) {
    size_t h = hash<string>{}(key);
    return h % array_size;
}

void hashMap::insert(string &word, Wrapper::WordInstance location){
    //compare load factor and expand if needed

    int index = hashfunc(word);
    while ((not arr[index].empty()) and 
        (arr[index].at(0).word != location.word)){
        index = (index + 1) % array_size;
    }

    //make sure that the same word in the same line and file isn't already 
    //inserted 
    if (!arr[index].empty() &&
      arr[index].back().file == location.file &&
      arr[index].back().stringLine == location.stringLine) {
      return;
  }

    arr[index].push_back(location);
    num_entries++; 
    //check if we need to resize after we inserted 
    if ((float)num_entries / array_size > max_load_factor) {
        resize(); 
    }   

    
}

vector<Wrapper::WordInstance> hashMap::lookup(std::string &word) {
    int bucket = hashfunc(word);
    // linear probing until we find an empty bucket or a matching word
    while (!arr[bucket].empty() &&
           arr[bucket].at(0).word != word) {
        bucket = (bucket + 1) % array_size;
    }

    if (arr[bucket].empty()) {
        // word was never inserted so we can just return an empty vector 
        return vector<Wrapper::WordInstance>{};
    }

    // found, return the bucket vector
    return arr[bucket];
}

void hashMap::resize() {
    //store the original array
    vector<Wrapper::WordInstance> *old_array = arr; 
    int old_size = array_size; 
    
    //update the size
    array_size *= 2; 
    arr = new vector<Wrapper::WordInstance> [array_size]; //doubled sized array
    num_entries = 0; 
    
    //insert the words into the doubled array 
    for (int i = 0; i < old_size; i++) {
        for (int j = 0; j < old_array[i].size(); j++) {
            insert(old_array[i][j].word, old_array[i][j]);
        }
    }

    delete [] old_array;
}

