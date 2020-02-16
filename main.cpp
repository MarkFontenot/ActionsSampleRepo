#include <iostream>
#include <fstream>
#include "DSVector.h"
#include "DSString.h"


using namespace std;

int main(int argc, char **argv) {
     //cout << "hello";
     DSString y("Hello My NAME iS JOnathan");
     DSString x("My NAME");

     //cout << y[y.contains(x)];
     //cout <<



    //cout << (char *) numero << "lol";
    //DSString second((char *)numero);









     //cout << y;
     DSVector<DSString> k;
     //DSVector<DSString> j;
     //j = k;
     //cout << j[0];
    ifstream keyWordsFile;
    keyWordsFile.open(argv[2]);
    char part [2048];
    DSVector<DSString> keyWords;
    DSString read;

    if(!keyWordsFile.is_open()){
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
     book.open(argv[1]);
     if(!book.is_open()){
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

     for(int x = 0; x < eachPage.getSize(); x++){
         out = eachPage[x];
         cout << out << endl;

     }

    //if(keyWords.find(read)){
        //cout << "We found: " << read << endl;
    //}


    //cout << k.find("ajgkjg");
    //k.append(2);
    //cout << k[0];
    //cout << "Hello, World!" << endl;
    ofstream fout("output01.txt");
    fout << "Hello world!" << endl;
    fout.close();
    return 0;
}
