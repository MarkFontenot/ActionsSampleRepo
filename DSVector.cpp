//
// Created by Jonathan Ebrahimian on 2/13/20.
//

#include "DSVector.h"


template <class T>
DSVector<T>::DSVector() {
    data = new T[10];
    cap = 10;
    size = 0;

}

template <class T>
int DSVector<T>::getSize(){
    return size;
}


template <class T>
DSVector<T>::DSVector(const DSVector<T> & input) {
    data = new T[input.getSize()];
    for(int x = 0; x < size; x++){
        data[x] = input[x];
    }
}

template <class T>
DSVector<T>::~DSVector() {
    delete [] data;
}

template <class T>
bool DSVector<T>::operator<(const DSVector<T> & r) const {
    if(!data[0] < r.data){
        return false;
    }else{
        return true;
    }
}


template <class T>
void DSVector<T>::append(T x) {
    if(size + 1 == cap){
        resize();
        data[size + 1] = x;
    }else{
        data[size + 1] = x;
    }
    size += 1;
}


template <class T>
T DSVector<T>::operator[](int x) {
    //if the index requested is larger than the char array return the last element of the array
    if(cap < x){
        return data[cap];
    }else{
        return data[x];
    }

}
//private
template <class T>
void DSVector<T>::resize(){
    T * temp = new T[cap * 2];
    for(int i = 0; i < cap; i++){
        temp[i] = data[i];
    }
    cap *= 2;
    delete [] data;
    data = temp;
}

