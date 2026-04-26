/*
 *   hashMap.cpp
 *   Marcus Ho and Jakov Maronhic
 *   2026-04-24
 *   CS 15 Project 4: gerp
 *
 *   Implements the hashMap class, which stores WordInstances (word, file
 *   index, line index) in a bucket array and supports insertion, lookup,
 *   and automatic resizing when the load factor is exceeded.
 */

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include "hashMap.h"
#include "wrapper.h"
using namespace std;

/*
 * name: hashMap()
 * purpose: Constructs an empty hash map with a default bucket array size
 *          and zero stored entries
 * arguments: none
 * returns: none
 * effects: Allocates the bucket array and sets num_entries to 0
 */
hashMap::hashMap(){
    array_size = 20;
    num_entries = 0;
    arr = new vector<hashMap::WordInstance> [array_size];
}

/*
 * name: ~hashMap()
 * purpose: Destroys the hash map and releases its memory
 * arguments: none
 * returns: none
 * effects: Deletes the dynamically allocated bucket array
 */
hashMap::~hashMap(){
    delete[] arr;
}

/*
 * name: hashfunc()
 * purpose: Computes which bucket a key belongs to
 * arguments: the key (string) to hash
 * returns: an integer bucket index within arr
 * effects: none
 */
int hashMap::hashfunc(string key) {
    size_t h = hash<string>{}(key);
    return h % array_size;
}

/*
 * name: insert()
 * purpose: Records one occurrence of a word at a specific file and line,
 *          skipping the insert if that exact occurrence is already stored
 * arguments: the word (string), the file index, and the line index where
 *            the word was found
 * returns: none
 * effects: Adds a WordInstance to the appropriate bucket (with linear
 *          probing), increments num_entries, and may trigger a resize if
 *          the load factor is exceeded
 */
void hashMap::insert(std::string &word, int file, int stringLine){
    //compare load factor and expand if needed

    int index = hashfunc(word);
    WordInstance location;
    location.word = word;
    location.file = file;
    location.stringLine = stringLine;
    while ((not arr[index].empty()) and 
        (arr[index].at(0).word != location.word)){
        index = (index + 1) % array_size;
    }

    //make sure that the same word in the same line and file isn't already 
    //inserted 
    if ((not arr[index].empty()) and
      arr[index].back().file == location.file and
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

/*
 * name: lookup()
 * purpose: Finds every stored occurrence whose key matches the given word
 * arguments: the word (string) to search for
 * returns: a vector of WordInstances for that word (empty if not found)
 * effects: none
 */
vector<hashMap::WordInstance> hashMap::lookup(std::string &word) {
    int bucket = hashfunc(word);
    // linear probing until we find an empty bucket or a matching word
    while ((not arr[bucket].empty()) and
           arr[bucket].at(0).word != word) {
        bucket = (bucket + 1) % array_size;
    }

    if (arr[bucket].empty()) {
        // word was never inserted so we can just return an empty vector 
        return vector<hashMap::WordInstance>{};
    }

    // found, return the bucket vector
    return arr[bucket];
}

/*
 * name: resize()
 * purpose: Doubles the bucket array size and redistributes every stored
 *          WordInstance to keep the load factor low
 * arguments: none
 * returns: none
 * effects: Replaces arr with a larger array, rehashes all entries by
 *          calling insert again, and frees the old array
 */
void hashMap::resize() {
    //store the original array
    vector<hashMap::WordInstance> *old_array = arr; 
    int old_size = array_size; 
    
    //update the size
    array_size *= 2; 
    arr = new vector<hashMap::WordInstance> [array_size]; //doubled sized array
    num_entries = 0; 
    
    //insert the words into the doubled array 
    for (int i = 0; i < old_size; i++) {
        for (size_t j = 0; j < old_array[i].size(); j++) {
            insert(old_array[i][j].word, old_array[i][j].file, 
                    old_array[i][j].stringLine);
        }
    }

    delete [] old_array;
}