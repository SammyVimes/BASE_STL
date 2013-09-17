#ifndef STACK_H
#define STACK_H

#include "List.h"

using namespace std;

template <class T> class Stack {

public:
    void push(T element) {
        list->add(element, 0);
    }

    T pop() {
        Node<T>* head = list->getHead();
        if (head == NULL) {
            return NULL;
        }
        T element = head->get();
        list->remove(0);
        return element;
    }

    int getSize() {
        return list->getSize();
    }

    Stack() {
        list = new List<T>();
    }

    ~Stack() {
        delete list;
    }

private:
    List<T>* list;
};

#endif // STACK_H
