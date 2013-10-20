#include <iostream>
#include "BinaryTree.h"

int main() {
    BinaryTree<int>* tree = new BinaryTree<int>();
    Node<int>* root = tree->getRoot();
    root->set(1);
    root->setLeft(2);
    root->setRight(3);
    Node<int>* left = root->getLeft();
    Node<int>* right = root->getRight();
    Node<int>* el = NULL;
    left->setLeft(999);
    left->setRight(11);
    right->setLeft(5);
    Node<int>* tmp = right->getLeft();
    tmp->setLeft(100);
    tmp->setRight(1248);
    tmp = tmp->getRight();
    tmp->setLeft(1000000);
    tmp->setRight(999);
    el = left;
    left = el->getLeft();
    right = el->getRight();
    left->setLeft(19);
    right->setRight(21);
    int quantity = 0;
    bool exists = false;
    int val = 1000000;
    BinaryTree<int>::WideIterator* iter = tree->getIterator();
    tmp = iter->getNext();
    while(tmp) {
        if (tmp->get() == val) {
            quantity++;
            exists = true;
        }
        tmp = iter->getNext();
    }
    delete iter;
    cout << exists << endl << quantity << endl;
    cout << endl << tree->branchesToGo(val) << endl;
    return 0;
}
