//
// Created by Jonathan Ebrahimian on 2/13/20.
//

#include "DSString.h"
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

/*Default constructor
 * This constructor simply assigns data to a null terminating character.
 *
 * Params: N/A
 * Return: N/A
 */
DSString::DSString(){
    data = new char[1];
    data[0] = '\0';
}

/*Overloaded constructor
 * This constructor recieves a char * and creates a DSString
 * with the char * as its contents.
 *
 * Params: char *
 * Return: N/A
 */
DSString::DSString(char* input){
    //creates a new character array of the length of the input + 1
    //for the null terminating character and assigns it to data
    data = new char[strlen(input) + 1];
    strcpy(data,input);//copies the input into the newly created char array

}

/*Copy construcor
 * The copy constructor creates a copy of DSString.
 *
 * Params: DSString
 * Return: N/A
 */
DSString::DSString(const DSString & input) {
    data = new char[strlen(input.data) + 1];
    strcpy(data,input.data);
}


/*Destructor
 * Deallocates memory
 *
 * Params: N/A
 * Return: N/A
 */
DSString::~DSString(){
    delete[] data;//deletes dynamically allocated data from DSString
}

/*Contains
 * This method checks if the current DSString contains the parameter passed in.
 * And returns the index at which is was found.
 *
 * Params: DSString
 * Return: int
 */
int DSString::contains(DSString & input) {
    bool start  = false;
    int indexFound = -1;

    int lengthOfParam = strlen(input.data);//finds how long the parameter is

    //iterates through the current DSString's data
    for(int x = 0; x < strlen(data); x++){

        //checks if the current character is equal to the
        //first character in the params data
        if(data[x] == input.data[0]) {
            start = true;//starts checking to see if all of the param is contained in the current DSString
            indexFound = x;

            //iterates through the param's data
            for (int j = 0; j < lengthOfParam; j++) {

                //checks if the current DSString is at the end before
                //finding all elements of param's data
                if (x + j > strlen(data)){
                    return -1;
                }else {

                    //checks to see if the current element in the current DSString's data
                    //is equal to the current element in the param's data
                    if (data[x + j] != input.data[j]) {

                        //indicates that the current DSString does not contain the param's data at this point
                        start = false;
                        indexFound = -1;
                    }
                }
            }

            //if start was never changed to false then the DSString does contain the param's data
            if (start) {
                return indexFound;
            }
        }
    }
    return -1;//returns false if the param's data is not found after iterating through the whole string
}



/* getLength
 * Gets the length of the data
 *
 * Params: N/A
 * Return: int
 */
int DSString::getLength()  {
    return strlen(data);
}

/* Assignment operator
 * This method assigns the right side to the left side.
 * This method is for assigning a DSString to a DSString
 *
 * Params: DSString
 * Return: DSString
 */
DSString& DSString::operator=(const DSString& input) {
    delete[] data;//clears current data

    data = new char[strlen(input.data) + 1];
    //cout << input.data;
    strcpy(data, input.data);//copies the inputs data to the current DSStrings data

    return *this;
}

/* Assignment operator
 * This method assigns the right side to the left side.
 * This method is for assigning a char * to a DSString
 *
 * Params: char *
 * Return: DSString
 */
DSString& DSString::operator=(const char * input) {
    delete[] data;//clears current data

    data = new char[strlen(input) + 1];

    strcpy(data, input);//copies the input to the current DSStrings data

    return *this;
}

/* Addition operator
 * This method concatinates the left side with the right side of the + operator.
 *
 * Params: DSString
 * Return: DSString
 */
DSString DSString::operator +(const DSString rhs){
    char * temp = new char[strlen(data) + strlen(rhs.data) + 1];

    int i = 0;

    //iterates through the current DSString's data
    while(data[i] != '\0'){
        temp[i] = data[i];
        i++;
    }
    temp[i] = '\0';
    strcat(temp,rhs.data);//concatenates the param's data to temp

    DSString temp2;
    temp2 = temp;
    delete [] temp;//deletes the previously allocated data
    return temp2;
}

/* Equals operator
 * This method checks if 2 DSStrings are equal.
 *
 * Params: DSString
 * Return: bool
 */
bool DSString::operator  == (const DSString& input){
    //compares the data of the current DSString to the input
    //strcmp will return 0 if they are equal
    return strcmp(data,input.data) == 0;
}

/* Less than operator
 * This method checks if the left of the operator is less than the right.
 *
 * Param: DSString
 * Return: bool
 */
bool DSString::operator < (const DSString& input) const
{
    //compares the data of the current DSString to the input
    //strcmp will return a value less than 0 if
    //the left side is less than the right
    return strcmp(data, input.data) < 0;
}

/* Greater than operator
 * This method checks if the left of the operator is greater than the right.
 *
 * Param: DSString
 * Return: bool
 */
bool DSString::operator > (const DSString& comp) const
{
    //compares the data of the current DSString to the input
    //strcmp will return a value greater than 0 if
    //the left side is greater than the right
    return strcmp(data, comp.data) > 0;
}

/* Ostream operator
 * This method allows DSString to be printed through the ostream operator.
 *
 * Params: ostream, DSString
 * Return: ostream
 */
ostream& operator << (ostream& oStreamIn, DSString & input){
    oStreamIn << input.data;//puts the inputs data to the ostream
    return oStreamIn;
}

/* Istream operator
 * This operator allows DSString to be instantiated through the istream operator.
 *
 * Params: istream, DSString
 * Return: istream
 */
istream& operator >>(istream& inStreamIn, DSString& input){
    char* newString = new char[500];//creates new char array of size 500

    //gets characters from the inStream
    //and puts them into the newly created char array
    inStreamIn.get(newString,500);

    input = newString;
    delete[] newString;//deallocate the previously created char array

    return inStreamIn;
}

/* substring
 * This method allows DSStrings to be substringed.
 * Similar to regular substrings the last index is NOT inclusive.
 *
 * Params: int, int
 * Return: DSString
 */
DSString DSString::substring(int firstIndex, int secondIndex) {
   //cout << firstIndex << endl;
   // cout << secondIndex << endl;
    if(firstIndex > secondIndex){
        cout << "Invalid indexes" << endl;
        exit(1);
    }
    //no need for + 1 because secondIndex isn't inclusive
    char * temp = new char[secondIndex - firstIndex + 1];

    int i = 0;
    //data[firstIndex] != '\0' &&

    while(data[firstIndex] != '\0' && firstIndex < secondIndex){
        temp[i] = data[firstIndex];
        firstIndex++;
        i++;
    }

    temp[i] = '\0';

    DSString temp2;
    temp2 = temp;


    delete [] temp;//deallocate the previously created char array
    return temp2;
}

/*c_str
 * gets the DSStrings data
 *
 * Param: N/A
 * Return: char *
 */
char * DSString::c_str() {
    return data;//returns data of current DSString
}

/* index operator
 * This operator allows the user to use the index operator
 * in order to get a certain index of the DSString.
 *
 * Params: int
 * Return: char
 */
char DSString::operator[](int x) {
    //if the index requested is larger than the char array return the last element of the array
    if(strlen(data) < x){
        cout << "Index out of bounds";
        exit(1);
    }else{
        return data[x];
    }

}

/*lowercase
 * This method makes every character in the DSString lowercase
 *
 * Params: N/A
 * Return: void
 */

void DSString::lowercase() {
    //no need for + 1 because secondIndex isn't inclusive
    for(int x = 0; x < strlen(data); x++){
        data[x] = tolower(data[x]);
    }
}

DSString &DSString::operator=(const int input) {
    delete[] data;//clears current data

    int n = input;
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    if(input == 0){
        count = 1;
    }
    data = new char[count + 1];
    //char array [count];
    int number = input;
    for (int i = count-1; i >= 0; i--) {
        int x = (number % 10);
        char c = '0' + x;
        data[i] = c;
        number /= 10;
    }
    data[count] = '\0';

    return *this;
}

DSVector<DSString> DSString::split(char splitter []) {
    DSVector<DSString> result;
    DSString temp;

    char *token = strtok(data, splitter);


    while (token != NULL)
    {
        temp = token;
        result.append(temp);
        token = strtok(NULL, splitter);
    }

    return result;
}

//DSString DSString::operator+(char rhs) {
//    char * temp = new char[strlen(data) + 1];
//
//
//    int i = 0;
//
//    //iterates through the current DSString's data
//    while(data[i] != '\0'){
//        temp[i] = data[i];
//        i++;
//    }
////    temp[i] = rhs;
////   temp++;
//    temp[i] = '\0';
//    //strcat(temp,rhs);
//
//    DSString temp2;
//    temp2 = temp;
//    delete [] temp;//deletes the previously allocated data
//    //delete [] rhsData;
//    return temp2;
//}

int DSString::getInt() {
    return atoi(data);
}
