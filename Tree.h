#ifndef TREE_H
#define TREE_H
#include "List.h"
#include "Stack.h"

template <class T> class TreeNode;

template <class T> class Tree {
public :
    Tree() {
        root = new TreeNode<T>();
    }

    ~Tree() {
        /*
        * Implement with wide search
        */
    }

    TreeNode<T> getRoot() {
        return root;
    }

    class WideIterator {

    };

    class DepthIterator {

    };

private :
    TreeNode<T> root;
};

template <class T> class TreeNode {
public:

    TreeNode() {
        children = new List<T>();
    }

    List<TreeNode<T>*> getChildren() {
        return children;
    }

    T getElement() {
        return element;
    }

    void setValue(const T value) {
        this->value = value;
    }

    void addChildren() {
        children->add(new TreeNode<T>());
    }

private:
    T value;
    List<TreeNode<T>*> children;

};

#endif // TREE_H
