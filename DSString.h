//
// Created by Jonathan Ebrahimian on 2/13/20.
//

#ifndef INC_20S_PA02_AUTOINDEXER_DSSTRING_H
#define INC_20S_PA02_AUTOINDEXER_DSSTRING_H


#include <iostream>
#include "DSVector.h"
#include <cstring>
using namespace std;

class DSString {
private:
    char * data;//contains the characters of the DSString
public:
    //Constructors
    DSString();//Default constructor
    DSString(char *);//Overloaded char * constructor
    DSString(const DSString&);//copy constructor
    ~DSString();//Destructor

    //overloaded operators
    DSString &operator=(const DSString&);//assignment operator
    DSString &operator=(const char*);//assignment operator
    DSString &operator=(const int);
    DSString operator+(DSString rhs);//addition operator
    DSString operator+(char rhs);//addition operator
    bool operator<(const DSString&)const;//less than operator
    bool operator>(const DSString&)const;//greater than operator
    bool operator==(const DSString&);//equals operator
    friend ostream& operator <<(ostream& , DSString &);//out stream
    friend istream& operator >>(istream& , DSString &);//in stream

    //special functions
    int contains(DSString & str);
    int getInt();
    char operator[](int);
    DSString substring(int, int);
    void lowercase();
    DSVector<DSString> split(char []);



    //getters
    int getLength();
    char* c_str();
};


#endif //INC_20S_PA02_AUTOINDEXER_DSSTRING_H
