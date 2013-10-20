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
    left->setLeft(10);
    left->setRight(11);
    right->setLeft(5);
    el = left;
    left = el->getLeft();
    right = el->getRight();
    left->setLeft(19);
    right->setRight(21);
    cout << tree->branchesToGo(19) << endl;
    return 0;
}
