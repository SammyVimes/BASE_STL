#include <iostream>
#include "QueryVector.h"

int main()
{
    ArrayVector<int>* query = new ArrayVector<int>();
    query->add(0); //0
    query->add(1); //1
    query->add(0); //2
    query->add(0); //3
    query->add(0); //4
    query->add(1); //5
    query->add(1); //6
    query->add(0); //7
    query->add(0); //8
    query->add(0); //9
    query->add(1); //10
    query->add(0); //11
    query->add(1); //12
    query->add(1); //13
    query->add(1); //14
    query->add(0); //15
    query->add(1); //16
    query->add(0); //17
    query->add(0); //18
    query->add(0); //19
    query->add(0); //20
    query->add(1); //21
    query->add(1); //22

    query->remove(0);
    query->remove(2);
    query->remove(3);
    query->remove(4);
    query->remove(5);
    query->remove(7);
    query->remove(8);
    query->remove(9);
    query->remove(11);
    query->remove(15);
    query->remove(17);
    query->remove(18);
    query->remove(19);
    query->remove(7);
    query->doReform();
    for(int i = 0; i < query->getSize(); i++) {
        cout << query->get(i) << endl;
    }
    return 0;
}
