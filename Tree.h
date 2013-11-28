#ifndef TREE_H
#define TREE_H
#include "List.h"
#include "Stack.h"

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

    void setChildren(List<TreeNode<T>*>* children) {
        this->children = children;
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

    void setValue(T value) {
        this->value = value;
    }

    void addChildren() {
        children->add(new TreeNode<T>());
    }

    void addChildren(T value) {
        TreeNode<T>* node = new TreeNode<T>();
        node->getValue(value);
        children->add(node);
    }

    void addChildren(TreeNode<T>* node) {
        children->add(node);
    }

private:
    T value;
    List<TreeNode<T>*>* children;

};

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

    static Tree<T>* createFromString(char* string) {
        Tree<char>* tree = new Tree<char>();
        TreeNode<char>* root = tree->getRoot();
        root->setValue(string[0]);
        int n = 1;
        tree->fillTree(string, root, n);
        return tree;
    }

    List<TreeNode<T>*>* fillTree(char* string, TreeNode<T>* parent, int &n) {
        TreeNode<T>* cur = parent;
        List<TreeNode<T>*>* childrenList = new List<TreeNode<T>*>();
        while (true) {
            char ch = string[n];
            n++;
            if (ch == '(') {
                List<TreeNode<T>*>* tmp = fillTree(string, cur, n);
                for (int i = 0; i < tmp->getSize(); i++) {
                    cur->addChildren(tmp->get(i));
                }
            } else if (ch == ')') {
                if (string[n + 1] == '(') {
                    continue;
                }
                break;
            } else if (ch == 0) {
                break;
            } else {
                cur = new TreeNode<T>();
                cur->setValue(ch);
                childrenList->add(cur);
            }
        }
        return childrenList;
    }

    char* toString() {
        Stack<TreeNode<T>*>* childStack = new Stack<TreeNode<T>*>();
        Stack<int>* childQuantityStack = new Stack<int>();
        int n = 0;
        int curSize = 1;
        char* str = new char[100]; //TODO: написать адекватное высчитывание длинны строки
        childStack->push(root);         //или использовать вектор
        while(true) {
            bool notEmpty = true;
            do {
                if (curSize == 0) {
                    str[n] = ')';
                    n++;
                    curSize = childQuantityStack->pop();
                    if (childQuantityStack->getSize() == 0) { //если TRUE, значит, мы только что
                        notEmpty = false;             //вытащили текущий номер для корня
                    }
                }
            } while(!curSize && notEmpty);
            TreeNode<T>* cur = childStack->pop();
            if (!cur) {
                str[n] = 0;
                str[n + 1] = 0;
                break;
            }
            str[n] = cur->getValue();
            n++;
            curSize--;
            List<TreeNode<T>*>* children = cur->getChildren();
            int size = children->getSize();
            if (size != 0) {
                childQuantityStack->push(curSize);
                curSize = size;
                str[n] = '(';
                n++;
            }
            for (int i = (size - 1); i >= 0; i--) {
                childStack->push(children->get(i));
            }
        }
        return str;
    }

    TreeNode<T>* getRoot() {
        return root;
    }

    void setRoot(TreeNode<char>* root) {
        this->root = root;
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

#endif // TREE_H
