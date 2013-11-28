#include <iostream>
#include <fstream>
#include <QFile>
#include <QString>
#include <QByteArray>
#include "AVLTree.h"

using namespace std;


int main() {
    AVLTree<int>* tree = new AVLTree<int>();
    AVLNode<int>* node = tree->getRoot();
    node->setLeft(5);
    node->setKey(5);
    bool isAvl = tree->isAVL();
    int key = node->get();
    return 0;
}
