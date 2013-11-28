#ifndef NODEFACTORY_H
#define NODEFACTORY_H
#include "BinaryTree.h"
#include "AVLTree.h"

class NodeFactory {

public :
    /*template <class T>
    static Node<T>* getNode(BinaryTree<T>* tree);*/
};

//template <class T>
//Node<T>* NodeFactory::getNode<T>(BinaryTree<T>* tree) {
//    if (tree->isAVL()) {
//        return new AVLNode<T>();
//    } else {
//        return new Node<T>();
//    }
//}

#endif // NODEFACTORY_H
