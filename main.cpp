#include <iostream>
#include "processing.h"
#include "wrapper.h"
using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Usage: ./gerp inputDirectory outputFile";
    exit(EXIT_FAILURE);
  }

  Wrapper index(argv[1]);
  ofstream outfile(argv[2]); 
  if (not outfile.is_open()) { 
    //cerr << "Could not open output file: " << argv[2] << endl; 
    return EXIT_FAILURE; 
  }

  string word; 
  while (true) {
    cout << "Query? "; 
    if (not (cin >> word)) {
        cout << "Goodbye! Thank you and have a nice day." << endl; 
        break;
    }

    if (word == "@q" or word == "@quit") {
      cout << "Goodbye! Thank you and have a nice day." << endl; 
      break;
    }

    else if (word == "@f") {
      string new_file; 
      cin >> new_file; 
      outfile.close(); 
      outfile.open(new_file); 
      if (not outfile.is_open()) {
        //cerr << "Could not open " << new_file 
        //   << " for writing." << endl; 
        break;
      }
    }

    else if (word == "@i" or word == "@insensitive") {
      string query; 
      if (not (cin >> query)) {
        cout << "Goodbye! Thank you and have a nice day." << endl; 
        break;
    } 
      index.search(false, query, outfile); 
    } 
        
    else {
      index.search(true, word, outfile); 
    }
  }

  return 0; 
}
