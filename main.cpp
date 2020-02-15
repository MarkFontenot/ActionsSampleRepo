#include <iostream>
#include <fstream>
#include "DSVector.h"
#include "DSString.h"


using namespace std;

int main(int argc, char **argv) {
     //cout << "hello";
     DSString y("hello");
     //cout << y;
     DSVector<DSString> k;
     k.append(y);
     k.append(y);
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
    int counter= 0;
    while(!keyWordsFile.eof()){
        //keyWordsFile.getline(part,500);
        keyWordsFile.getline(part,500,'\n');
        //keyWordsFile >> part;
        cout << part << endl;
        //read = part;
        //keyWords.append(read);

    }

     ifstream book;
     book.open(argv[1]);
     if(!book.is_open()){
         cout << "Error opening input file";
         return 1;
     }



     k.clear();

     while(!book.eof()){
         //book.getline(part, 200);
         book >> part;
         read = part;
         //cout << part << endl;
         k.append(read);
     }

//
    for(int x = 0; x < keyWords.getSize(); x ++){
        //y = keyWords[x];
        //cout << y << endl;
    }

    //cout << k.find("ajgkjg");
    //k.append(2);
    //cout << k[0];
    //cout << "Hello, World!" << endl;
    ofstream fout("output01.txt");
    fout << "Hello world!" << endl;
    fout.close();
    return 0;
}
