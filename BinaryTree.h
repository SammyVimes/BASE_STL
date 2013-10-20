#ifndef BINARYTREE_H
#define BINARYTREE_H


#include "QueryVector.h"

template <class T> class Node;

template <class T> class BinaryTree {



public:

    BinaryTree() {
        root = new Node<T>();
    }

    ~BinaryTree() {
        QueryVector<BinaryTree<T>*>* query = new QueryVector<BinaryTree*>();
        query->add(this->getRoot());
        while(query->getSize() > 0) {
            Node<T>* cur = query->get();
            query->add(cur->getLeft());
            query->add(cur->getRight());
            delete cur;
        }
    }

    int branchesToGo(const T elem) {
        QueryVector<Node<T>*>* query = new QueryVector<Node<T>*>();
        int floor = 0;
        int children = 1;
        int tmpChildren = 0;
        query->add(this->getRoot());
        while(true) {
            if (children <= 0) {
                children = tmpChildren;
                tmpChildren = 0;
                floor++;
            }
            if (query->getSize() == 0) {
                return -1;
            }
            Node<T>* cur = query->get();
            if (cur->get() == elem) {
                return floor;
            }
            Node<T>* left = cur->getLeft();
            Node<T>* right = cur->getRight();
            if (left == NULL && right == NULL) {
                children--;
                continue;
            }
            if (left != NULL) {
                query->add(left);
                tmpChildren++;
            }
            if (right != NULL) {
                query->add(right);
                tmpChildren++;
            }
            children--;
        }
    }

    Node<T>* getRoot() {
        return root;
    }

private:
    T elem;
    Node<T>* root;
};

template <class T> class Node {
public:
        Node() {
            left = NULL;
            right = NULL;
        }

        T get() {
            return elem;
        }

        void setRight(const T elem) {
            right = new Node<T>();
            right->set(elem);
        }

        void setLeft(const T elem) {
            left = new Node<T>();
            left->set(elem);
        }

        Node<T>* getLeft() {
            return left;
        }

        Node<T>* getRight() {
            return right;
        }

        void set(const T elem) {
            this->elem = elem;
        }

private:
        T elem;
        Node* left;
        Node* right;
};

#endif // BINARYTREE_H
