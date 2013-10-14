#include <iostream>
#include "QueryVector.h"

int main()
{
    ArrayVector<int>* query = new ArrayVector<int>();
    for (int i = 0; i < 160; i++) {
        query->add(i);
    }
    for (int i = 1; i < 15; i++) {
        query->remove(i);
    }
    cout << query->get(0) << "  " << query->get(1) << endl;
    return 0;
}
