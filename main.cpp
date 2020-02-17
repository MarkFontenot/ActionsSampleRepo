#include <iostream>
#include <fstream>
#include "DSVector.h"
#include "DSString.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"


using namespace std;

int main(int argc, char **argv) {
    //RUNNING CATCH TESTS
    //argc == 1
    if (argc == 1) {
        cout << "Running Catch Tests" << endl;
        return Catch::Session().run();
    }

     //cout << "hello";
     DSString y("Hello My NAME iS JOnathan");
     DSString x("My NAME");



     //cout << y;
     DSVector<DSString> k;
     //DSVector<DSString> j;
     //j = k;
     //cout << j[0];
    ifstream keyWordsFile;
    keyWordsFile.open(argv[1]);
    char part [2048];
    DSVector<DSString> keyWords;
    DSString read;
    //cout << "test";
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
     char  separator [] = ".:;\n";
     while(!book.eof()){

         book.getline(part, 200, ' ');


         pch = strtok(part,separator);
         while (pch != NULL){
             if(first){
                 read = pch;
                 read = read + " ";
                 first = false;
             }else{
                 read = read + pch + " ";
             }
             pch = strtok(NULL, separator);
         }
     }
     read.lowercase();

     bool stop = false;

     int page = 1;
     DSString pageNumber;
     DSString pageSearch;
     DSString starter("<");
     int indexStart;
     int indexEnd;
     DSVector<DSString> eachPage;




     while(!stop){
         pageNumber = page;
         pageSearch = starter + pageNumber + ">";
         //cout << pageSearch << endl;
         indexStart = read.contains(pageSearch);
         pageNumber = page + 1;
         pageSearch = starter + pageNumber + ">";
         //cout << pageSearch << endl;
         indexEnd = read.contains(pageSearch);
         if(indexStart == -1){
             stop = true;
         }else if(indexEnd == -1){
             stop = true;
             eachPage.append(read.substring(indexStart,read.getLength()-1));
         }else{
             eachPage.append(read.substring(indexStart,indexEnd));
         }
         page++;
     }
     DSString out;
     DSString word;
     DSString temp2;
     DSString temp3(": ");
     keyWords.sort();
     DSVector<DSString> pagesAppeared;
     DSString temp;

     for(int j = 0; j < keyWords.getSize(); j++){
        pagesAppeared.append("-1");
     }



     for(int x = 0; x < eachPage.getSize(); x++){
         out = eachPage[x];
         //cout << out << endl;
         for(int j = 0; j < keyWords.getSize(); j++){
             word = keyWords[j];
             if(out.contains(word) != -1){
                 temp = pagesAppeared[j];
                 temp2 = (x+1);


                 if(pagesAppeared[j] == "-1"){
                     temp2 = temp3 + temp2;
                     pagesAppeared.edit(temp2,j);
                 } else{
                     temp = temp + ", " + temp2;
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




    //if(keyWords.find(read)){
        //cout << "We found: " << read << endl;
    //}


    //cout << k.find("ajgkjg");
    //k.append(2);
    //cout << k[0];
    //cout << "Hello, World!" << endl;

    return 0;
}
