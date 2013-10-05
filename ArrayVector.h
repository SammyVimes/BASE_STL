#ifndef ARRAYVECTOR_H
#define ARRAYVECTOR_H

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

    T remove(const int i) {
        if (i < 0 || i >= arrayLength || size <= 0) {
            return NULL;
        }
        T elem = array[i];
        array[i] = NULL;
        size--;
        recentlyRemovedQuantity++;
        if (recentlyRemovedQuantity > 12) {
            if (arrayLength > 12) {
                decreaseMemory();
                recentlyRemovedQuantity = 0;
            }
        }
        return elem;
    }

    int getSize() {
        return size;
    }

    int getArrayLength() {
        return arrayLength;
    }

    void doReform() {
        if (arrayLength - size > 12) {
            decreaseMemory();
            recentlyRemovedQuantity = 0;
        } else {
            reform();
        }
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
        size = count;
        arrayLength -= 12;
        delete tmpQuery;
    }

    void reform() {
        T prev;
        for (int i = 0; i < arrayLength; i++) {
            T cur = array[i];
            if (i != 0) {
                if (prev == NULL) {
                    array[i - 1] = cur;
                    array[i] = NULL;
                }
            }
            prev = array[i];
        }
    }

    void increaseMemory() {
        T* tmpQuery = array;
        arrayLength += 12;
        array = new T[arrayLength];
        for (int i = 0; i < arrayLength; i++) {
            array[i] = NULL;
        }
        for (int i = 0; i < size; i++) {
            array[i] = tmpQuery[i];
        }
        delete tmpQuery;
    }
};

#endif // ARRAYVECTOR_H
