/*
 *   main.cpp
 *   Marcus Ho and Jakov Maronhic
 *   2026-04-24
 *   CS 15 Project 4: gerp
 *
 *   Entry point for the gerp program. Validates command-line arguments,
 *   builds the Wrapper index over the given directory, and runs the
 *   interactive query loop until the user quits or EOF is reached.
 */

#include <iostream>
#include "processing.h"
#include "wrapper.h"
using namespace std;

/*
 * name: main()
 * purpose: Entry point for the gerp program; validates command-line
 *          arguments, builds the index, and runs the interactive query
 *          loop (handling @q/@quit, @f, @i/@insensitive, and plain
 *          sensitive queries) until the user quits or EOF is reached
 * arguments: argc and argv from the command line (expects the input
 *            directory and an output file name)
 * returns: EXIT_SUCCESS on normal shutdown, EXIT_FAILURE on bad usage
 *          or an output file that cannot be opened
 * effects: Builds the Wrapper index, reads queries from cin, and writes
 *          results to the output file (which may change via @f)
 */
int main(int argc, char *argv[])
{
	if (argc != 3) {
		cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
		return EXIT_FAILURE;
	}

	Wrapper index(argv[1]);
	ofstream outfile(argv[2]); 
	if (!outfile.is_open()) {
		cerr << "Could not open output file: " << argv[2] << endl;
		return EXIT_FAILURE; 
	}
	
	string word; 
	while (true) {
		cout << "Query? "; 
		if (!(cin >> word)) {
				cout << "Goodbye! Thank you and have a nice day." << endl; 
				break;
		}

		if (word == "@q" || word == "@quit") {
			cout << "Goodbye! Thank you and have a nice day." << endl; 
			break;
		}

		else if (word == "@f") {
			string new_file; 
			cin >> new_file; 
			outfile.close(); 
			outfile.open(new_file); 
			if (!outfile.is_open()) {
				cerr << "Could not open " << new_file 
					 << " for writing." << endl; 
			}
		}

		else if (word == "@i" || word == "@insensitive") {
			string query; 
			cin >> query; 
			index.search(false, query, outfile); 
		} 
        
		else {
			index.search(true, word, outfile); 
		}
	}

	return 0; 
}
