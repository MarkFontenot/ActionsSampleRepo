//
// Created by Jonathan Ebrahimian on 2/13/20.
//

#ifndef INC_20S_PA02_AUTOINDEXER_DSVECTOR_H
#define INC_20S_PA02_AUTOINDEXER_DSVECTOR_H
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class DSVector{
private:
    T * data;
    int size;
    int cap;

    //private function
    void resize();
public:
    DSVector<T>();//default constructor
    DSVector<T>(const DSVector&);//copy constructor
    ~DSVector();//Destructor

    //operators
    DSVector &operator=(const DSVector<T> &);//assignment
    bool operator==(const DSVector<T>&);//equality
    T operator[](int);//index

    //special functions
    void edit(T, int);
    void sort();
    void append(T);
    void removeAt(int);
    void clear();
    bool isEmpty();
    bool find(T);

    //getters
    int getSize()const;
};

/*Constructor
 * Dynamically allocates an array of type T and size 10.
 * Assigns capacity to 10 and size to 0.
 *
 *  Return: N/A
 */
template <class T>
DSVector<T>::DSVector() {
    //dynamically allocates array of type T w/ size 10
    data = new T[10];
    cap = 10;
    size = 0;
}

/*getSize
 * Returns the size of the vector.
 *
 * Return: int
 */
template <class T>
int DSVector<T>::getSize()const{
    return size;
}

/*copy constructor
 * Creates a copy of DSVector.
 *
 * Return: N/A
 */
template <class T>
DSVector<T>::DSVector(const DSVector<T> & input){
    //dynamically allocates array of type T w/ size of input
    data = new T[input.size];

    //copies data from input to current DSVector
    for(int x = 0; x < size; x++){
        data[x] = input.data[x];
    }

    //copies size and cap from input
    size = input.size;
    cap = input.cap;
}

/* Assignment Operator
 * Allows a vector to be assigned to another vector.
 *
 * Return: DSVector<T>&
 */
template <class T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T> & input) {
    delete[] data;//deallocates data
    data = new T[input.cap];//dynamically allocates array of type T w/ size 10

    //copies data from input to current DSVector
    for(int x = 0; x < input.size; x++){
        data[x] = input.data[x];
    }

    //copies size and cap from input
    size = input.size;
    cap = input.cap;
    return *this;
}

/* isEmpty
 * Returns true if vector is empty and false otherwise.
 *
 * Return: Bool
 */
template <class T>
bool DSVector<T>::isEmpty(){
    //checks size of array
    if(size == 0){
        return true;
    }else{
        return false;
    }
}


/*Destructor
 * Removes all dynamically allocated data.
 *
 * Return: N/A
 */
template <class T>
DSVector<T>::~DSVector() {
    delete [] data;
}

/*Append
 * Adds an element at the end of the vector.
 *
 * Return: void
 */
template <class T>
void DSVector<T>::append(T input) {
    //checks if size is at capacity of vector
    if(size == cap){
        resize();
        data[size] = input;//adds input to data
    }else{
        data[size] = input;//adds input to data
    }
    size += 1;//increases size
}

/*Clear
 * Clears all elements in the vector.
 *
 * Return: void
 */
template <class T>
void DSVector<T>::clear() {
    delete [] data;//clears data

    //creates new dynamically allocated array and resets cap and size
    data = new T[10];
    cap = 10;
    size = 0;
}

/*Edit
 * Changes the value of the element at the index passed in
 * to the value that was passed in.
 *
 * Return: void
 */
template <class T>
void DSVector<T>::edit(T input, int index) {
    //index out of bounds check
    if(index < 0 || index > size - 1){
        throw out_of_range("out of range in edit function");
    }
    data[index] = input;//changes value at desired index
}


/* Index operator
 * Returns the element at the index passed into
 * the index operator.
 *
 * Return: T
 */
template <class T>
T DSVector<T>::operator[](int input) {
    //index out of bounds checking
    if(input < 0 || input > size - 1){
        throw out_of_range("out of range in [] function");
    }
    return data[input];//returns data at desired index
}

/* Find
 * Checks if the element passed in is present in the vector.
 *
 * Return: Bool
 */
template <class T>
bool DSVector<T>::find(T input) {
    //iterates through vector checking if an element is equal to the input
    for(int x = 0; x < size; x++){
        if(data[x] == input){
            return true;
        }
    }
    return false;//returns false if nothing was found
}

/* Sort
 * Sorts the vector from least to greatest value using bubble sort.
 *
 * Return: void
 */
template <class T>
void DSVector<T>::sort(){
    //bubble sort
    T temp;
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            //swaps if lhs is smaller than rhs
            if(data[i] > data[j]){
                temp  = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}



/* Equality operator
 * Checks if two DSVectors are equal to each other. Returns true if they
 * are and false if they are not.
 *
 * Return: Bool
 */
template <class T>
bool DSVector<T>::operator==(const DSVector<T> & input) {
    //if vectors are not the same size
    if(input.size != size){
        return false;
    }

    //iterates through data
    for(int x = 0; x < size; x++){
        //returns false once the lhs is not = to the rhs
        if(!(data[x] == input.data[x])){
            return false;
        }
    }
    return true;//returns true if no differences are found
}

/* RemoveAt
 * Removes element at index requested.
 *
 * Return: void
 */
template <class T>
void DSVector<T>::removeAt(int input) {
    //index out of bounds check
    if(input < 0 || input > size -1){
        throw out_of_range("out of range in removeAt function");
    }

    //creates new array with same capacity
    T * newData = new T[cap];
    int counter = 0;

    //iterates through data
    for(int x = 0; x < size;x++){
        //adds element to newData when we are not at the index requested
        if(x != input){
            newData[counter] = data[x];
            counter++;
        }
    }
    delete [] data;//deallocates old data
    size = size - 1;//lowers size by one
    data = newData;//assigns newData to data
}

//private
/* Resize
 * Private function used to double the capacity of the vector,
 * copy over the data from the smaller vector, and deallocate the
 * smaller vector. (Only gets called when size = cap when appending)
 *
 * Return: void
 */
template <class T>
void DSVector<T>::resize(){
    //dynamically allocates array of type T w/ size * 2
    T * temp = new T[cap * 2];
    //copies data from old data to new data
    for(int i = 0; i < cap; i++){
        temp[i] = data[i];
    }
    cap *= 2;//increases capacity
    delete [] data;//deallocates old data
    data = temp;//assigns data to new larger array
}
#endif //INC_20S_PA02_AUTOINDEXER_DSVECTOR_H
