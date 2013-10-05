#include <iostream>
#include "ArrayVector.h"

int main()
{
    ArrayVector<int>* vector = new ArrayVector<int>();
    for (int i = 1; i < 15; i++) {
        vector->add(i);
    }
    for (int i = 0; i < 13; i++) {
        vector->remove(i);
    }
    for (int i = 0; i < vector->getSize(); i++) {
        cout << vector->get(i) << endl;
    }
    return 0;
}
