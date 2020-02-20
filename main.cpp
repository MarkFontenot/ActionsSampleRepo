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

int main(int argc, char **argv) {
    //RUNNING CATCH TESTS
    //argc == 1
    if (argc == 1) {
        cout << "Running Catch Tests" << endl;
        return Catch::Session().run();
    }
    char part [80];

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
        keyWordsFile.getline(part,80,'\n');
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
     DSVector<DSString> rawPages;
     int pageCounter = 0;
     DSString tempString;
     read = "";
     while(!book.eof()){

         book.getline(part, 80, '\n');
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

     read.lowercase();



    // cout << read;
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
    //cout << read;

//     while(!stop){
//         pageNumber = page;
//         //pageSearch = starter + pageNumber + (char *)">";
//         //cout << pageSearch;
//         indexStart = indexEnd;
//         if(firstIteration){
//             indexStart = 0;
//             firstIteration = false;
//         }
//
//         //indexStart = read.contains(pageSearch);
//         pageNumber = page + 1;
//         pageSearch = starter + pageNumber + (char *)">";
//         //cout << pageSearch << endl;
//         indexEnd = read.contains(pageSearch);
//
//
//         if(indexStart == -1){
//             stop = true;
//         }else if(indexEnd == -1){
//             stop = true;
//             //temp5 = read.substring(indexStart,read.getLength()-1);
//             //cout << temp5 << endl;
//
//             eachPage.append(read.substring(indexStart,read.getLength()-1));
//         }else{
//             //temp5 = read.substring(indexStart,indexEnd);
//             //cout << temp5 << endl;
//             eachPage.append(read.substring(indexStart,indexEnd));
//             //read = read.substring(indexEnd,read.getLength()-1);
//         }
//         cout << endl << endl;
//         page++;
//     }
     DSString out;
     DSString word;
     DSString temp2;
     DSString temp3((char *)": ");
     keyWords.sort();
     DSVector<DSString> pagesAppeared;
     DSString temp;
     DSString end((char *)">");

     for(int j = 0; j < keyWords.getSize(); j++){
        pagesAppeared.append((char *)"-1");
     }


     //DSVector<DSVector<int>> pagesInside;


    for(int x = 0; x < rawPages.getSize(); x++){
        for(int j = 0; j < keyWords.getSize(); j++){
            tempString = rawPages[x];
            keyWordTemp = keyWords[j];
            tempString.lowercase();
            keyWordTemp.lowercase();

            if(tempString.contains(keyWordTemp) != -1){
                temp = pagesAppeared[j];
                temp2 = tempString.substring(1,tempString.contains(end));
                if(pagesAppeared[j] == (char *)"-1"){
                    temp2 = temp2;
                    pagesAppeared.edit(temp2,j);
                } else{
                    temp = temp + (char *)", " + temp2;
                    pagesAppeared.edit(temp,j);
                }
            }
        }

        //cout << tempString << endl;
    }

//     for(int x = 0; x < eachPage.getSize(); x++){
//         out = eachPage[x];
//         //cout << out << endl;
//         for(int j = 0; j < keyWords.getSize(); j++){
//             word = keyWords[j];
//             if(out.contains(word) != -1){
//                 temp = pagesAppeared[j];
//                 temp2 = (x+1);
//
//
//                 if(pagesAppeared[j] == (char *)"-1"){
//                     temp2 = temp3 + temp2;
//                     pagesAppeared.edit(temp2,j);
//                 } else{
//                     temp = temp + (char *)", " + temp2;
//                     pagesAppeared.edit(temp,j);
//                 }
//             }
//         }
//
//     }
     char currLetter;
     char nextLetter;
    ofstream fout;
    fout.open(argv[3]);
    DSString tempInt;
    DSVector<DSString> result;
    DSVector<int> intResults;
    int lengthOfLine;
    for(int j = 0; j < keyWords.getSize(); j++) {
        nextLetter = keyWords[j][0];
        if(currLetter != nextLetter){
            currLetter = nextLetter;
            fout << "[" << nextLetter << "]" << endl;
        }
        word = keyWords[j];
        temp = pagesAppeared[j];
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
        lengthOfLine = 0;
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
