//
// Created by Jonathan Ebrahimian on 2/13/20.
//

#ifndef INC_20S_PA02_AUTOINDEXER_DSVECTOR_H
#define INC_20S_PA02_AUTOINDEXER_DSVECTOR_H

template <class T>
class DSVector{
private:
    T * data;
    int size;
    int cap;
    void resize();
public:
    DSVector<T>();
    DSVector<T>(const DSVector&);
    ~DSVector();
    //include copy constructor
    //include destructor
    //include assignment operator
    bool operator <(const DSVector<T> & r) const;
    DSVector &operator=(const DSVector<T> &);//assignment operator
    bool operator==(const DSVector<T>&);

    void edit(T, int);
    void sort();
    T operator[](int);
    void append(T);
    void removeAt(int);
    int getSize()const;
    void clear();
    bool isEmpty();
    bool find(T);
    void makeUnique();



    //sort
    //binary search
    //simple search

};

template <class T>
DSVector<T>::DSVector() {
    data = new T[10];
    cap = 10;
    size = 0;
}

template <class T>
int DSVector<T>::getSize()const{
    return size;
}


template <class T>
DSVector<T>::DSVector(const DSVector<T> & input){
    //std::cout << size;
    data = new T[input.getSize()];
    for(int x = 0; x < size; x++){
        data[x] = input.data[x];
    }
}

template <class T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T> & input) {
    delete[] data;
    data = new T[input.cap];
    for(int x = 0; x < input.size; x++){
        data[x] = input.data[x];
    }
    size = input.size;
    cap = input.cap;
    return *this;
}

template <class T>
bool DSVector<T>::isEmpty(){
    if(size == 0){
        return true;
    }else{
        return false;
    }
}

template <class T>
DSVector<T>::~DSVector() {
    //if(size != 0){
    delete [] data;
    //}
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
    if(size == cap){
        resize();
        data[size] = x;
    }else{
        data[size] = x;
    }
    size += 1;
}

template <class T>
void DSVector<T>::clear() {
    delete [] data;
    data = new T[10];
    cap = 10;
    size = 0;
}

template <class T>
void DSVector<T>::edit(T input, int index) {
    data[index] = input;
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

template <class T>
bool DSVector<T>::find(T input) {
    for(int x = 0; x < size; x++){
        if(data[x] == input){
            return true;
        }
    }
    return false;
}

template <class T>
void DSVector<T>::sort() {
    T temp;
    for(int i=0;i<size;i++)
    {
        for(int j=i+1;j<size;j++)
        {
            if(data[i]>data[j])
            {
                temp  =data[i];
                data[i]=data[j];
                data[j]=temp;
            }
        }
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

template <class T>
bool DSVector<T>::operator==(const DSVector<T> & input) {
    if(input.size != size){
        return false;
    }
    for(int x = 0; x < size; x++){
        if(!(data[x] == input.data[x])){
            return false;
        }
    }
    return true;
}

template <class T>
void DSVector<T>::removeAt(int input) {
    //delete [] data;
    T * newData = new T[size-1];
    int counter = 0;
    for(int x = 0; x < size;x++){
        if(x != input){
            newData[counter] = data[x];
            counter++;
        }
    }
    delete [] data;
    size = size - 1;
    data = newData;

}
#endif //INC_20S_PA02_AUTOINDEXER_DSVECTOR_H
