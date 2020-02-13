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
    DSVector();
    DSVector(const DSVector&);
    ~DSVector();
    //include copy constructor
    //include destructor
    //include assignment operator
    bool operator <(const DSVector<T> & r) const;
    T operator[](int);
    void append(T);
    int getSize();

    //sort
    //binary search
    //simple search

};


#endif //INC_20S_PA02_AUTOINDEXER_DSVECTOR_H
