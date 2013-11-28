#ifndef QUERYLIST_H
#define QUERYLIST_H

#include "List.h"

using namespace std;

template <class T> class QueryList {

public:

    void add(const T element) {
        query->add(element, 0);
    }

    T get() {
        T element = query->get(getSize() - 1);
        query->remove(getSize() - 1);
        return element;
    }

    int getSize() {
        return query->getSize();
    }

    QueryList() {
        query = new List<T>();
    }

    ~QueryList() {
        delete query;
    }

private:
    List<T>* query;
};

#endif // QUERYLIST_H
