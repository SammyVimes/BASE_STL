#include <iostream>
#include "QueryVector.h"

int main()
{
    QueryVector<int>* query = new QueryVector<int>();
    for (int i = 1; i < 160; i++) {
        query->add(i);
    }
    int size = query->getSize();
    for (int i = 0; i < size; i++) {
        cout << query->get() << endl;
    }
    return 0;
}
