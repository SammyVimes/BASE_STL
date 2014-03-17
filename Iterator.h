#ifndef ITERATOR_H
#define ITERATOR_H

template <class T> class Iterator {

public:
    virtual T next() = 0;
    virtual bool hasNext() = 0;
    virtual T current() = 0;
};

#endif // ITERATOR_H
