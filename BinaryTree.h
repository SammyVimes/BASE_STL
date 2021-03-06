#ifndef BINARYTREE_H
#define BINARYTREE_H


#include "QueryVector.h"
#include "NodeFactory.h"

template <class T> class Node;

template <class T> class BinaryTree {



public:

    BinaryTree() {
        _isAVL = false;
        root = new Node<T>();
    }

    ~BinaryTree() {
        QueryVector<Node<T>*>* query = new QueryVector<Node<T>*>();
        query->add(this->getRoot());
        while(query->getSize() > 0) {
            Node<T>* cur = query->get();
            query->add(cur->getLeft());
            query->add(cur->getRight());
            delete cur;
        }
    }

    void setRoot(Node<T>* root) {
        this->root = root;
    }

    void setIsAVL(bool _isAVL) {
       this->_isAVL = _isAVL;
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

    bool isAVL() {
        return _isAVL;
    }


    class WideIterator {
    public:
        WideIterator(BinaryTree<T>* tree) {
            this->tree = tree;
            Node<T>* root = this->tree->getRoot();
            query = new QueryVector<Node<T>*>();
            query->add(root);
        }

        Node<T>* getNext() {
            cur = query->get();
            if (cur == NULL) {
                return NULL;
            }
            Node<T>* left = cur->getLeft();
            Node<T>* right = cur->getRight();
            if (left != NULL) {
                query->add(left);
            }
            if (right != NULL) {
                query->add(right);
            }
            return cur;
        }

    private:
        QueryVector<Node<T>*>* query;
        Node<T>* cur;
        BinaryTree<T>* tree;
    };


    WideIterator* getIterator() {
        return new WideIterator(this);
    }

private:
    T elem;
    Node<T>* root;
    bool _isAVL;
};

template <class T> class Node {
public:
        Node() {
            elem = NULL;
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


        void setLeftPointer(Node<T>* left) {
            this->left = left;
        }

        void setRightPointer(Node<T>* right) {
            this->right = right;
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
