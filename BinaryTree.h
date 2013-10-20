#ifndef BINARYTREE_H
#define BINARYTREE_H


#include "QueryVector.h"

template <class T> class BinaryTree {



public:

    int branchesToGo(const T elem) {
        QueryVector<BinaryTree*>* query = new QueryVector<BinaryTree*>();
        int floor = 0;
        int children = 1;
        int tmpChildren = 0;
        query->add(this);
        while(true) {
            if (children <= 0) {
                children = tmpChildren;
                tmpChildren = 0;
                floor++;
            }
            if (query->getSize() == 0) {
                return -1;
            }
            BinaryTree<T>* cur = query->get();
            if (cur->get() == elem) {
                return floor;
            }
            BinaryTree<T>* left = cur->getLeft();
            BinaryTree<T>* right = cur->getRight();
            if (left == NULL || right == NULL) {
                continue;
            }
            query->add(left);
            query->add(right);
            children--;
            tmpChildren += 2;
        }
    }

    BinaryTree<T>* getLeft() {
        return left;
    }

    BinaryTree<T>* getRight() {
        return right;
    }

    T get() {
        return elem;
    }

private:
    T elem;
    BinaryTree<T>* left;
    BinaryTree<T>* right;
};

#endif // BINARYTREE_H
