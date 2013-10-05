#ifndef LIST_H
#define LIST_H

#include <stddef.h>

using namespace std;

template <class T> class Node;

template <class T> class List {

public:
        List() {
                head = NULL;
                tail = NULL;
                size = 0;
        }
        T get(const int n) {
                if (n > size - 1) {
                        return NULL;
                }
                T returnValue = NULL;
                Node<T> *cur = head;
                for (int i = 0; i < (n + 1); i++) {
                        if (i != n) {
                                cur = cur->getNext();
                        }
                        else {
                                returnValue = cur->get();
                        }
                }
                return returnValue;
        }

        int getSize() {
                return size;
        }

        void add(const T value) {
                if (head == NULL) {
                        head = new Node<T>();
                        head->setValue(value);
                        tail = head;
                }
                else {
                        Node<T> *newElement = new Node<T>();
                        newElement->setValue(value);
                        tail->setNext(newElement);
                        tail = newElement;
                }
                size++;
        }



        char* toString() {
            char* string = new char[2*size + 1];
            Node<T>* cur = head;
            int count = 0;
            while (cur != NULL) {
                string[count] = cur->get();
                count++;
                string[count] = ' ';
                cur = cur->getNext();
                count++;
            }
            string[count] = 0;
            return string;
        }

        bool hasElem(const T value) {
                bool res = false;
                bool ololo = false;
                Node<T>* cur = head;
                while (cur != 0) {
                        T curVal = cur->get();
                        if (value == curVal) {
                            return true;
                        }
                        cur = cur->getNext();
                }
                return ololo;
        }

        void addIfNotExist(const T value) {
            if (!hasElem(value)) {
                add(value);
            }
        }

        void add(const T value, int position) {
                Node<T>* newNode = new Node<T>();
                newNode->setValue(value);
                if (position < 0) {
                        position = 0;
                }
                if (position > size) {
                        tail->setNext(newNode);
                        tail = newNode;
                        size++;
                        return;
                }
                Node<T>* curElem = head;
                int count = 0;
                Node<T>* prevElem = NULL;
                do {
                        if (count == position) {
                                if (curElem == head) {
                                        newNode->setNext(head);
                                        head = newNode;
                                }
                                else {
                                        newNode->setNext(curElem);
                                        prevElem->setNext(newNode);
                                }
                                size++;
                                break;
                        }
                        count++;
                        prevElem = curElem;
                        curElem = curElem->getNext();
                } while (curElem != NULL);
        }

        Node<T>* getHead() {
                return this->head;
        }

        Node<T>* getTail() {
                return this->tail;
        }

        void remove(const int n) {
                Node<T>* curElem = head;
                int count = 0;
                Node<T>* prevElem = NULL;
                while (curElem != NULL) {
                        if (count == n) {
                                if (prevElem == NULL) {
                                        head = curElem->getNext();
                                }
                                else if (curElem == tail) {
                                        prevElem->setNext(NULL);
                                        tail = prevElem;
                                }
                                else {
                                        prevElem->setNext(curElem->getNext());
                                }
                                delete curElem;
                                break;
                        }
                        else {
                                prevElem = curElem;
                                curElem = curElem->getNext();
                        }
                        count++;
                }
                size--;
        }

private:
        Node<T> *head;
        Node<T> *tail;
        int size;
};

template <class T> class Node {
public:
        Node() {
                next = NULL;
        }

        T get() {
                return value;
        }

        void setNext(Node<T> *next) {
                this->next = next;
        }

        Node<T>* getNext() {
                return next;
        }
        void setValue(const T value) {
                this->value = value;
        }
private:
        T value;
        Node *next;
};

#endif // LIST_H
