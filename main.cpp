#include <iostream>
#include <fstream>
#include "DSVector.h"
#include "DSString.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"



using namespace std;
void addPageNumbers(char **,char []);

int main(int argc, char **argv) {
    //RUNNING CATCH TESTS
    //argc == 1
    if (argc == 1) {
        cout << "Running Catch Tests" << endl;
        return Catch::Session().run();
    }
    char part [2048];

    //addPageNumbers(argv, part);





     DSVector<DSString> k;


    ifstream keyWordsFile;
    keyWordsFile.open(argv[1]);

    DSVector<DSString> keyWords;
    DSString read;

    if(!keyWordsFile){
        cout << "Error opening input file";
        return 1;
    }

    while(!keyWordsFile.eof()){
        keyWordsFile.getline(part,500,'\n');
        read = part;
        read.lowercase();
        keyWords.append(read);
    }

     ifstream book;
     book.open(argv[2]);
     if(!book){
         cout << "Error opening input file";
         return 1;
     }

     k.clear();
     bool first = true;
     char * pch;
     char  separator [] = ".:,;\n";

     while(!book.eof()){

         book.getline(part, 200, ' ');
         //cout << part;

         pch = strtok(part,separator);
         while (pch != NULL){
             if(first){
                 read = pch;
                 read = read + (char *)" ";
                 first = false;
             }else{
                 read = read + pch + (char *)" ";
             }
             pch = strtok(NULL, separator);
         }
     }
     read.lowercase();

     bool stop = false;

     int page = 1;
     DSString pageNumber;
     DSString pageSearch;
     DSString starter((char *)"<");
     int indexStart;
     int indexEnd;
     DSVector<DSString> eachPage;
     bool firstIteration = true;

     DSString temp5;
    //cout << read;
     while(!stop){
         pageNumber = page;
         //pageSearch = starter + pageNumber + (char *)">";
         //cout << pageSearch;
         indexStart = indexEnd;
         if(firstIteration){
             indexStart = 0;
             firstIteration = false;
         }

         //indexStart = read.contains(pageSearch);
         pageNumber = page + 1;
         pageSearch = starter + pageNumber + (char *)">";
         //cout << pageSearch << endl;
         indexEnd = read.contains(pageSearch);
         cout << indexStart << endl;
         cout << indexEnd << endl;


         if(indexStart == -1){
             stop = true;
         }else if(indexEnd == -1){
             stop = true;
             //temp5 = read.substring(indexStart,read.getLength()-1);
             //cout << temp5 << endl;

             eachPage.append(read.substring(indexStart,read.getLength()-1));
         }else{
             //temp5 = read.substring(indexStart,indexEnd);
             //cout << temp5 << endl;
             eachPage.append(read.substring(indexStart,indexEnd));
             read = read.substring(indexStart,indexEnd);
         }
         cout << endl << endl;
         page++;
     }
     DSString out;
     DSString word;
     DSString temp2;
     DSString temp3((char *)": ");
     keyWords.sort();
     DSVector<DSString> pagesAppeared;
     DSString temp;

     for(int j = 0; j < keyWords.getSize(); j++){
        pagesAppeared.append((char *)"-1");
     }



     for(int x = 0; x < eachPage.getSize(); x++){
         out = eachPage[x];
         //cout << out << endl;
         for(int j = 0; j < keyWords.getSize(); j++){
             word = keyWords[j];
             if(out.contains(word) != -1){
                 temp = pagesAppeared[j];
                 temp2 = (x+1);


                 if(pagesAppeared[j] == (char *)"-1"){
                     temp2 = temp3 + temp2;
                     pagesAppeared.edit(temp2,j);
                 } else{
                     temp = temp + (char *)", " + temp2;
                     pagesAppeared.edit(temp,j);
                 }
             }
         }

     }
     char currLetter;
     char nextLetter;
    ofstream fout;
    fout.open(argv[3]);


    for(int j = 0; j < keyWords.getSize(); j++) {
        nextLetter = keyWords[j][0];
        if(currLetter != nextLetter){
            currLetter = nextLetter;
            fout << "[" << nextLetter << "]" << endl;
        }
        word = keyWords[j];
        temp = pagesAppeared[j];
        fout << word << temp << endl;
    }
    fout.close();

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
        rawBook.getline(part,1028,'\n');
        finalBook << part << " ";
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

