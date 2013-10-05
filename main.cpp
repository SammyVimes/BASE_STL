#include <iostream>
#include "ArrayVector.h"

int main()
{
    ArrayVector<int>* vector = new ArrayVector<int>();
    for (int i = 1; i < 100; i++) {
        vector->add(i);
    }
    for (int i = 0; i < 13; i++) {
        vector->remove(10 + i);
        cout << "+" << endl;
    }
    for (int i = 0; i < vector->getSize(); i++) {
        cout << vector->get(i) << endl;
    }
    return 0;
}
