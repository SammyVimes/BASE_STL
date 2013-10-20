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
    cout << tree->branchesToGo(999) << endl;
    return 0;
}
