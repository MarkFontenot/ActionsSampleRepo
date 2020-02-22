#include <iostream>
#include <fstream>
#include "DSVector.h"
#include "DSString.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"



using namespace std;
void addPageNumbers(char **,char []);
int getNumDigits(int);
DSVector<DSString> getKeyWords(char **,char []);
DSVector<DSString> getEachPage(char **, char []);
DSVector<DSString> getPagesForEachWord(DSVector<DSString>&, DSVector<DSString>&);
void writeToOutputFile(char **, DSVector<DSString>&, DSVector<DSString>&);

int main(int argc, char **argv) {
    //RUNNING CATCH TESTS
    //argc == 1

    if (argc == 1) {
        cout << "Running Catch Tests" << endl;
        return Catch::Session().run();
    }
    char part [81];

    //addPageNumbers(argv, part);



    cout << "We are in" << endl;

     DSVector<DSString> keyWords;
     keyWords = getKeyWords(argv,part);

    cout << "We have the keywords" << endl;


    DSVector<DSString> rawPages;
    rawPages = getEachPage(argv,part);

    cout << "We have the pages in" << endl;


    DSVector<DSString> pagesAppeared;
    pagesAppeared = getPagesForEachWord(keyWords,rawPages);
    cout << "We know where the key words appear" << endl;

    //cout << pagesAppeared.getSize();

    writeToOutputFile(argv,keyWords,pagesAppeared);

    cout << "We have written to output file" << endl;


    return 0;
}

void addPageNumbers(char ** argv, char part []){

    ifstream rawBook;
    rawBook.open("rawBook.txt");
    if(!rawBook){
        cout << "File did not open" << endl;
    }

    ofstream finalBook;
    finalBook.open(argv[2]);

    int counter = 0;
    int pageNumber = 2;
    finalBook << "<";
    finalBook << 1;
    finalBook << "> " << endl;
    while(!rawBook.eof()){
        rawBook.getline(part,80,'\n');
        finalBook << part << endl;
        //cout << part;
        counter++;
        if(counter == 10){
            finalBook << endl;
            finalBook << "<";
            finalBook << pageNumber;
            finalBook << ">" << endl;
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

int getNumDigits(int x){
    int count = 0;
    while (x != 0) {
        x = x / 10;
        ++count;
    }
    return count;
}


DSVector<DSString> getKeyWords(char ** argv, char part []){
    ifstream keyWordsFile;
    keyWordsFile.open(argv[1]);

    DSVector<DSString> keyWords;
    DSString read;

    if(!keyWordsFile){
        cout << "Error opening input file key words";
        exit(1);
    }
    char * pch;
    char  separator [] = ".?!:,;\n";

    while(!keyWordsFile.eof()){
        keyWordsFile.getline(part,80,'\n');
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


        read.lowercase();

        if(!keyWords.find(read)){
            //cout << read << "   this is the read" << endl;
            keyWords.append(read);
        }

        read = "";
    }
    keyWordsFile.close();
    return keyWords;
}

DSVector<DSString> getEachPage(char ** argv, char part []){
    ifstream book;
    book.open(argv[2]);
    if(!book){
        cout << "Error opening input file book";
        exit(1);
    }
    DSString read;
    bool first = true;
    char * pch;
    char  separator [] = " .?-\"\t!:,;\n";
    DSVector<DSString> rawPages;
    int pageCounter = 0;
    DSString tempString;
    read = "";
    while(!(tempString == (char *)"<-1>")){

        book.getline(part, 81, '\n');
        tempString = part;
        //cout << part << endl;
        if(tempString[0] == '<' && tempString[tempString.getLength() -1] == '>' && !first) {
            //cout << "new page" << endl;
            //if(!first){
            //cout << read << endl;
            rawPages.append(read);

            //}

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
    }

    return rawPages;
}

DSVector<DSString> getPagesForEachWord(DSVector<DSString> & keyWords, DSVector<DSString> & rawPages){
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
                //cout << temp << endl;
                int lastIndex = tempString.contains(end);
                temp2 = tempString.substring(1,lastIndex);
                if(temp == (char *)"-1"){
                    //temp2 = temp2;
                    cout << temp2 << endl;
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


void writeToOutputFile(char ** argv, DSVector<DSString>& keyWords, DSVector<DSString>& pagesAppeared){
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
        fout.open(argv[3]);
        DSString tempInt;
        DSVector<DSString> result;
        DSVector<int> intResults;
        int lengthOfLine;
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