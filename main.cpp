#include <iostream>
#include "Stack.h"

int main()
{
    Stack<int>* stack = new Stack<int>();
    for (int i = 0; i < 10; i++) {
        stack->push(i);
    }
    for (int i = 0; i < 10; i++) {
        cout << stack->pop();
    }
    return 0;
}
