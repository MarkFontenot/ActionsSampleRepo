//
// Created by Jonathan Ebrahimian on 2/27/20.
//

#ifndef INC_20S_PA02_AUTOINDEXER_INDEXER_H
#define INC_20S_PA02_AUTOINDEXER_INDEXER_H

#include "DSString.h"
#include "DSVector.h"
#include <iostream>

class Indexer {
private:
    void addPageNumbers(char **);
    DSVector<DSString> getKeyWords(char *,char []);
    DSVector<DSString> getEachPage(char *, char []);
    DSVector<DSString> getPagesForEachWord(DSVector<DSString>&, DSVector<DSString>&);
    void writeToOutputFile(char *, DSVector<DSString>&, DSVector<DSString>&);
public:
    //Indexer();
    void indexBook(char*,char*,char*);
};


#endif //INC_20S_PA02_AUTOINDEXER_INDEXER_H
