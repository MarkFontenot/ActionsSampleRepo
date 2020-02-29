#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Indexer.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    //RUNNING CATCH TESTS
    if(argc == 1){
        cout << "Running Catch Tests" << endl;
        return Catch::Session().run();
    }
    Indexer s;
    s.indexBook(argv[2],argv[1],argv[3]);

    return 0;
}
