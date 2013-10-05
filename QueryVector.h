#ifndef QUERYVECTOR_H
#define QUERYVECTOR_H

#include "ArrayVector.h"

template <class T> class QueryVector {

public:
    QueryVector() {
        query = new ArrayVector<T>();
    }

    ~QueryVector() {
        delete query;
    }

    void add(const T element) {
        query->add(element);
    }

    T get() {
        T element = query->get(0);
        query->remove(0);
        return element;
    }

private:
    ArrayVector<T>* query;
};

#endif // QUERYVECTOR_H
