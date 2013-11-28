#ifndef AVLTREE_H
#define AVLTREE_H
#include "BinaryTree.h"
#include "Stack.h"

template <class T> class AVLNode;

template <class T> class AVLTree : public BinaryTree<T> {

public:

    AVLTree() {
        this->setIsAVL(true);
        root = new AVLNode<T>();
    }

    void insert(int key) {
        Stack<AVLNode<T>*>* trip = new Stack<AVLNode<T>*>();
        Stack<int>* leftOrRight = new Stack<int>(); //0 - left, 1 - right
        trip->push(root);
        while(true) {
            AVLNode<T>* cur = trip->peek();
            int curKey = cur->getKey();
            if (key < curKey) {
                AVLNode<T>* left = cur->getLeft();
                if (left == NULL) {
                    cur->setLeft(0);
                    cur->getLeft()->setKey(key);
                    break;
                }
                trip->push(left);
                leftOrRight->push(0);
            } else {
                AVLNode<T>* right = cur->getRight();
                if (right == NULL) {
                    cur->setRight(0);
                    cur->getRight()->setKey(key);
                    break;
                }
                trip->push(right);
                leftOrRight->push(1);
            }
        }
        AVLNode<T>* tmp = trip->pop();
        while(trip->getSize()) {
            tmp = tmp->balance();
            AVLNode<T>* cur = trip->pop();
            if (cur != NULL) {
                int t = leftOrRight->pop();
                if (t) {
                    cur->setRightPointer(tmp);
                } else {
                    cur->setLeftPointer(tmp);
                }
            }
            tmp = cur;
        }
    }

    AVLNode<T>* getRoot() {
        return root;
    }

private :
    bool _isAVL;
    AVLNode<T>* root;

};

template <class T> class AVLNode : public Node<T> {
public:
        AVLNode() {
            elem = NULL;
            left = NULL;
            right = NULL;
            height = 1;
        }

        T get() {
            return elem;
        }

        void fixheight() {
            unsigned char hl = getLeft() ? getLeft()->getHeight() : 0;
            unsigned char hr = getRight() ? getRight()->getHeight() : 0;
            height = (hl > hr ? hl : hr) + 1;
        }

        int balanceFactor() {
            unsigned char hl = getLeft() ? getLeft()->getHeight() : 0;
            unsigned char hr = getRight() ? getRight()->getHeight() : 0;
            return hr - hl;
        }

        int getHeight() {
            return height;
        }

        AVLNode<T>* rotateRight() {
            AVLNode<T>* left = getLeft();
            this->left = left->getRight();
            left->setRightPointer(this);
            fixheight();
            left->fixheight();
            return left;
        }

        AVLNode<T>* rotateLeft() {
            AVLNode<T>* right = getRight();
            this->right = right->getLeft();
            right->setLeftPointer(this);
            fixheight();
            right->fixheight();
            return right;
        }

        AVLNode<T>* balance() {
            fixheight();
            if(balanceFactor() == 2 )
            {
                if(getRight()->balanceFactor() < 0 ) {
                    setRightPointer(getRight()->rotateRight());
                }
                return rotateLeft();
            }
            if(balanceFactor() == -2 )
            {
                if(getLeft()->balanceFactor() > 0  ) {
                    setLeftPointer(getLeft()->rotateLeft());
                }
                return rotateRight();
            }
            return this; // балансировка не нужна
        }

        void setRight(const T elem) {
            right = new AVLNode<T>();
            right->set(elem);
        }

        void setLeft(const T elem) {
            left = new AVLNode<T>();
            left->set(elem);
        }

        AVLNode<T>* getLeft() {
            return left;
        }

        AVLNode<T>* getRight() {
            return right;
        }

        void setLeftPointer(AVLNode<T>* left) {
            this->left = left;
        }

        void setRightPointer(AVLNode<T>* right) {
            this->right = right;
        }

        void setKey(int key) {
            this->key = key;
        }

        int getKey() {
            return key;
        }

        void set(const T elem) {
            this->elem = elem;
        }

private:
        T elem;
        AVLNode* left;
        AVLNode* right;
        int key;
        unsigned char height;
};


#endif // AVLTREE_H
