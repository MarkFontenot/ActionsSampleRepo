#include <iostream>
#include <fstream>
#include "DSVector.h"
#include "DSString.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Indexer.h"


using namespace std;


int main(int argc, char **argv) {
    //RUNNING CATCH TESTS
    //argc == 1
    if(argc == 1){
        cout << "Running Catch Tests" << endl;
        return Catch::Session().run();
    }
    Indexer s;
    s.indexBook(argv[1],argv[2],argv[4]);

    return 0;
}
