#ifndef QUERYVECTOR_H
#define QUERYVECTOR_H

using namespace std;

template <class T> class ArrayVector {

public:
    ArrayVector() {
        arrayLength = 12;
        size = 0;
        array = new T[arrayLength];
        recentlyRemovedQuantity = 0;
    }

    void add(const T element) {
        if (size >= arrayLength) {
            increaseMemory();
        }
        array[size] = element;
        size++;
    }



    T get(const int i) {
        if (i < 0 || i >= size) {
            return NULL;
        }
        return array[i];
    }

    void remove(const int i) {
        if (i < 0 || i >= size) {
            return;
        }
        array[i] = NULL;
        size--;
        recentlyRemovedQuantity++;
        if (recentlyRemovedQuantity > 12) {
            if (arrayLength > 12) {
                decreaseMemory();
                recentlyRemovedQuantity = 0;
            }
        }
    }

    int getSize() {
        return size;
    }

    int getArrayLength() {
        return arrayLength;
    }

    ~ArrayVector() {
        size = 0;
        arrayLength = 0;
        recentlyRemovedQuantity = 0;
        delete array;
    }

private:
    T* array;
    int arrayLength;
    int size;

    int recentlyRemovedQuantity;

    void decreaseMemory() {
        T* tmpQuery = array;
        array = new T[arrayLength - 12];
        int count = 0;
        for (int i = 0; i < arrayLength; i++) {
            if (tmpQuery[i] != NULL) {
                array[count] = tmpQuery[i];
                count++;
            }
        }
        arrayLength -= 12;
        delete tmpQuery;
    }

    void increaseMemory() {
        T* tmpQuery = array;
        arrayLength += 12;
        array = new T[arrayLength];
        for (int i = 0; i < size; i++) {
            array[i] = tmpQuery[i];
        }
        delete tmpQuery;
    }
};

#endif // QUERYVECTOR_H
