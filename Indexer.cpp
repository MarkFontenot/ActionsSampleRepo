//
// Created by Jonathan Ebrahimian on 2/27/20.
//
#include <iostream>
#include "DSString.h"
#include "Indexer.h"
#include "DSVector.h"
#include <fstream>

void Indexer::indexBook(char * keyWordsFileName, char * bookFileName,char * outputFileName) {
    char part [500];

    cout << "We are in" << endl;

    DSVector<DSString> keyWords;
    keyWords = getKeyWords(keyWordsFileName,part);

    cout << "We have the keywords" << endl;


    DSVector<DSString> rawPages;
    rawPages = getEachPage(bookFileName,part);

    cout << "We have the pages in" << endl;
    DSString temp;
    for(int x = 0;x < rawPages.getSize();x++){
        temp = rawPages[x];
        cout << temp << endl;
    }

    DSVector<DSString> pagesAppeared;
    pagesAppeared = getPagesForEachWord(keyWords,rawPages);
    cout << "We know where the key words appear" << endl;


    //cout << pagesAppeared.getSize();

    writeToOutputFile(outputFileName,keyWords,pagesAppeared);

    cout << "We have written to output file" << endl;

}
void Indexer::addPageNumbers(char ** argv){

    ifstream rawBook;
    rawBook.open(argv[3]);
    if(!rawBook){
        cout << "File did not open" << endl;
        exit(1);
    }
    char part [100];

    ofstream finalBook;
    finalBook.open(argv[2]);

    int counter = 0;
    int pageNumber = 2;
    finalBook << "<";
    finalBook << 1;
    finalBook << "> " << endl;
    while(!rawBook.eof()){
        rawBook.getline(part,90,'\n');
        finalBook << part << endl;
        cout << part << endl;
        counter++;
        if(counter == 10){
            finalBook << endl;
            finalBook << "<";
            finalBook << pageNumber;
            finalBook << ">" << endl;
            cout << pageNumber << endl;
            pageNumber++;
            counter = 0;
        }
    }
    finalBook << endl;
    finalBook << "<";
    finalBook << -1;
    finalBook << ">";
    finalBook.close();
    rawBook.close();
}



DSVector<DSString> Indexer::getKeyWords(char * keyWordFileName, char part []){
    ifstream keyWordsFile;
    keyWordsFile.open(keyWordFileName);

    DSVector<DSString> keyWords;
    DSString read;

    if(!keyWordsFile){
        cout << "Error opening input file key words";
        exit(1);
    }
    char * pch;
    char  separator [] = ".?!:,;\"/\\[]{}\n";

    while(!keyWordsFile.eof()){
        keyWordsFile.getline(part,1000,'\n');
        pch = strtok(part,separator);
        while (pch != NULL){
//                 if(first){
//                     read = pch;
//                     read = read + (char *)" ";
//                     first = false;
//                 }else{
            read = read + pch;
//                 }
            pch = strtok(NULL, separator);
        }
        //read = part;
        //cout << read << "   this is the read" << endl;
        read = read.remove((char *)"'");
        read.lowercase();
        //cout << read << "   this is the read" << endl;

        if(!keyWords.find(read)){
            //cout << read << "   this is the read" << endl;
            keyWords.append(read);
        }

        read = "";
    }
    keyWordsFile.close();
    return keyWords;
}

DSVector<DSString> Indexer::getEachPage(char * bookFileName, char part []){
    ifstream book;
    book.open(bookFileName);
    if(!book){
        cout << "Error opening input file book";
        exit(1);
    }
    DSString read;
    bool first = true;
    char * pch;
    char  separator [] = " .?\"\t!:/\\[]{},;\n";

    DSVector<DSString> rawPages;
    int pageCounter = 0;
    DSString tempString;
    read = "";
    DSString pageAt;
    bool isInt = true;
    while(!(tempString == (char *)"<-1>")){

        book.getline(part, 1000, '\n');
        tempString = part;
        //cout << part << endl;

        if(tempString[0] == '<' && tempString[tempString.getLength() -1] == '>' && !first) {
            //cout << "new page" << endl;
            //if(!first){
            //cout << read << endl;

            pageAt = tempString.substring(1,tempString.getLength() -1);
            cout << pageAt << endl;
            if(pageAt.getLength() > 1){
                cout << "we are inside this" << endl;
                for(int x = 1; x < pageAt.getLength(); x++){
                    cout << pageAt[x] << endl;
                    if(!isdigit(pageAt[x])){
                        isInt = false;
                        cout << "we have found false" << endl;
                    }
                }
            }else{
                if(!isdigit(pageAt[0])){
                    cout << "we have found false" << endl;
                    isInt = false;
                }
            }
            if(isInt){
                read = read.remove((char *)"'");
                rawPages.append(read);
                pageCounter++;
                read = tempString + (char *)" ";
            }else{
                first = false;
                pch = strtok(part,separator);
                while (pch != NULL){
//                 if(first){
//                     read = pch;
//                     read = read + (char *)" ";
//                     first = false;
//                 }else{
                    read = read + pch + (char *)" ";
//                 }
                    pch = strtok(NULL, separator);
                }
            }
        }else{
            first = false;
            pch = strtok(part,separator);
            while (pch != NULL){
                read = read + pch + (char *)" ";
                pch = strtok(NULL, separator);
            }
        }
        isInt = true;
    }

    return rawPages;
}

DSVector<DSString> Indexer::getPagesForEachWord(DSVector<DSString> & keyWords, DSVector<DSString> & rawPages){
    //DSString out;
    DSString word((char *)"");
    DSString temp2((char *)"");
    DSString temp3((char *)": ");
    keyWords.sort();
    DSVector<DSString> pagesAppeared;
    DSString temp((char *)"");
    DSString end((char *)">");
    DSString tempString((char *)"");
    DSString keyWordTemp;
    DSString space((char *)" ");

    for(int j = 0; j < keyWords.getSize(); j++){
        pagesAppeared.append((char *)"-1");
    }

    for(int x = 0; x < rawPages.getSize(); x++){
        for(int j = 0; j < keyWords.getSize(); j++){
            tempString = rawPages[x];
            keyWordTemp = space + keyWords[j] + space;
            tempString.lowercase();
            keyWordTemp.lowercase();
            //tempString << endl << endl;
            if(tempString.contains(keyWordTemp) != -1){
                temp = pagesAppeared[j];
                int lastIndex = tempString.contains(end);
                temp2 = tempString.substring(1,lastIndex);
                if(temp == (char *)"-1"){
                    pagesAppeared.edit(temp2,j);
                } else{
                    temp = temp + (char *)", " + temp2;
                    pagesAppeared.edit(temp,j);
                }
            }
        }
    }
    return pagesAppeared;
}


void Indexer::writeToOutputFile(char * fileOutputName, DSVector<DSString>& keyWords, DSVector<DSString>& pagesAppeared){
    bool stop = false;

    int page = 1;
    DSString pageNumber;
    DSString pageSearch;
    DSString starter((char *)"<");
    int indexStart;
    int indexEnd;
    DSVector<DSString> eachPage;
    bool firstIteration = true;

    DSString keyWordTemp;
    DSString temp;
    DSString word;
    DSString tempString;
    char currLetter;
    char nextLetter;
    ofstream fout;
    fout.open(fileOutputName);
    DSString tempInt;
    DSVector<DSString> result;
    DSVector<int> intResults;
    int lengthOfLine = 0;
    for(int j = 0; j < keyWords.getSize(); j++) {
        temp = pagesAppeared[j];
        if(!(temp == (char *)"-1")){
            nextLetter = keyWords[j][0];
            if(currLetter != nextLetter){
                currLetter = nextLetter;
                nextLetter = toupper(nextLetter);
                fout << "[" << nextLetter << "]" << endl;
            }
            word = keyWords[j];
            lengthOfLine += word.getLength();
            fout << word;
            //cout << temp << endl;
            result = temp.split((char *)", ");
            intResults.clear();
            for(int x = 0; x < result.getSize();x++){
                tempString = result[x];
                //cout << "This should be: " << tempString << " but is: " << tempString.getInt()<< endl;
                intResults.append(tempString.getInt());


            }
            intResults.sort();

            bool start = true;
            for(int x = 0; x < intResults.getSize();x++){
                if(start){
                    tempInt = intResults[x];
                    temp = (char *)": ";
                    temp = temp + tempInt;
                    lengthOfLine += temp.getLength();
                    start = false;
                }else {
                    if(lengthOfLine + 2 > 70){
                        //cout << "WE IN";
                        //temp = temp + '\n';
                        fout << temp << endl;
                        fout << "    ";
                        temp = "";
                        lengthOfLine = 4;
                    }else{
                        temp = temp + (char *) ", ";
                        lengthOfLine += 2;
                    }
                    tempInt = intResults[x];
                    if(lengthOfLine + tempInt.getLength() > 70){


                        fout << temp << endl;
                        fout << "    ";
                        temp = "";
                        lengthOfLine = 4;
                    }
                    temp = temp + tempInt;
                    lengthOfLine += tempInt.getLength();
                }
            }
            cout << temp;
            cout << endl << endl;
            //cout << lengthOfLine << ": this is the length of line" << endl;
            fout << temp << endl;
        }
        lengthOfLine = 0;
    }
    fout.close();
}

