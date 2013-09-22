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
        WideIterator* iterator = getIterator();
        TreeNode<T>* cur;
        while ((cur = iterator->getNext()) != NULL) {
            delete cur;
        }
    }

    TreeNode<T>* getRoot() {
        return root;
    }

    class WideIterator {
    public:
        WideIterator(Tree<T>* tree) {
            this->tree = tree;
            TreeNode<T>* root = this->tree->getRoot();
            query = new List<TreeNode<T>*>();
            query->add(root);
        }

        TreeNode<T>* getNext() {
            cur = query->get(0);
            query->remove(0);
            if (cur == NULL) {
                return NULL;
            }
            if (cur->hasChildren()) {
                List<TreeNode<T>*>* children = cur->getChildren();
                for (int i = 0; i < children->getSize(); i++) {
                    query->add(children->get(i));
                }
            }
            return cur;
        }

    private:
        List<TreeNode<T>*>* query;
        TreeNode<T>* cur;
        Tree<T>* tree;
    };


    WideIterator* getIterator() {
        return new WideIterator(this);
    }

    class DepthIterator {

    };

private :
    TreeNode<T>* root;
};

template <class T> class TreeNode {
public:

    TreeNode() {
        children = new List<TreeNode<T>*>();
    }

    ~TreeNode() {
        delete children;
    }

    List<TreeNode<T>*>* getChildren() {
        return children;
    }

    T getValue() {
        return value;
    }

    bool hasChildren() {
        bool res = true;
        if (children->getSize() == 0) {
            res = false;
        }
        return res;
    }

    void setValue(const T value) {
        this->value = value;
    }

    void addChildren() {
        children->add(new TreeNode<T>());
    }

private:
    T value;
    List<TreeNode<T>*>* children;

};

#endif // TREE_H
