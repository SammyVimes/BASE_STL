#include <iostream>
#include <fstream>
#include <QFile>
#include <QString>
#include <QByteArray>
#include "Tree.h"

using namespace std;

//Node<char>* enterTree(QString fileContent, int& n) {
//    char ch;
//    Node<char>* p = NULL;
//    Node<char>* q = NULL;
//    ch = fileContent.at(n).toLatin1();
//    n++;
//    if (ch=='/') {
//        return NULL;
//    } else {
//        p = enterTree(fileContent, n);
//        q = enterTree(fileContent, n);
//        Node<char>* tmp = new Node<char>();
//        tmp->set(ch);
//        tmp->setLeftPointer(p);
//        tmp->setRightPointer(q);
//        return tmp;
//    }
//}


int main() {
//    BinaryTree<char>* tree = new BinaryTree<char>();
//    char* filePath = new char[100];
//    filePath = "C:\\myFiles\\KLP.txt";
//    QString filename(filePath);
//    QFile file(filename);
//    if(!file.open(QIODevice::ReadOnly)) {

//    }
//    QByteArray a = file.readAll();
//    QString fileContent(a);
//    int n = 0;
//    tree->setRoot(enterTree(fileContent, n));
//    int z = tree->branchesToGo('j');
    char* string = "q(a(KP(v)RF)bc(def(12)(d(4))))";
    Tree<char>* tree = Tree<char>::createFromString(string);
    char* t = tree->toString();
    cout << endl << t << endl << endl;
    return 0;
}
