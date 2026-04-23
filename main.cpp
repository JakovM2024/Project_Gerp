#include <iostream>                     
#include "processing.h"  
#include <vector>                   
using namespace std;                                                                                               

int main() {                                                                                                       

    DirectoryProcessor processor;
    vector<string> files;
    processor.traverseDirectory("tester", files);
    /*                                                                                                            
    cout << "Test 1: \"!!!com-p!!!!\" -> \"" << stripNonAlphaNum("!!!com-p!!!!") << "\"" << endl;
    cout << "Test 2: \"...world...\" -> \"" << stripNonAlphaNum("...world...") << "\"" << endl;
    cout << "Test 3: \"hello\" -> \"" << stripNonAlphaNum("hello") << "\"" << endl;
    cout << "Test 4: \"!!!\" -> \"" << stripNonAlphaNum("!!!") << "\"" << endl;                                 
    cout << "Test 5: \"\" -> \"" << stripNonAlphaNum("") << "\"" << endl;
    cout << "Test 6: \"##hi there!!\" -> \"" << stripNonAlphaNum("##hi there!!") << "\"" << endl;               
    cout << "Test 7: \"a\" -> \"" << stripNonAlphaNum("a") << "\"" << endl;                                     
    */                                                                                                                     
    return 0;                                                                                                      
}                                                                                                                  
