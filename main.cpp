#include <iostream>
#include "Tree.h"

int main()
{
    /*TEST*/
    Tree<int>* tree = new Tree<int>();
    TreeNode<int>* root = tree->getRoot();
    root->setValue(999);
    root->addChildren();
    root->addChildren();
    root->addChildren();
    TreeNode<int>* mid;
    List<TreeNode<int>*>* children = root->getChildren();
    for (int i = 0; i < children->getSize(); i++) {
        TreeNode<int>* cur = children->get(i);
        if (i == 1) {
            mid = cur;
        }
        cur->setValue(i);
    }
    mid->addChildren();
    children = mid->getChildren();
    children->get(0)->setValue(1111);
    Tree<int>::WideIterator* iter = NULL;
    iter = tree->getIterator();
    TreeNode<int>* cur;
    cur = iter->getNext();
    while(cur != NULL) {
        int val = cur->getValue();
        int a = 0;
        a++;
        cur = iter->getNext();
    }
    return 0;
}
