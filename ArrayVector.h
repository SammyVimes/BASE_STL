#ifndef ARRAYVECTOR_H
#define ARRAYVECTOR_H

using namespace std;
#define NULL_FLAG 0

typedef unsigned char byte;

template <class T> class ArrayVector {

public:

    ArrayVector() {
        arrayLength = 12;
        size = 0;
        array = pickMemory(arrayLength);
        metaData = pickMetadataMemory(arrayLength);
        recentlyRemovedQuantity = 0;
    }

    void add(const T element) {
        if (size >= arrayLength) {
            increaseMemory();
        }
        array[size] = element;
        setMetadataValue(size, 1);
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
        setMetadataValue(i, 0);
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
        delete metaData;
    }

private:
    T* array;
    byte* metaData;
    int arrayLength;
    int size;

    int recentlyRemovedQuantity;

    void decreaseMemory() {
        T* tmpArray = array;
        byte* tmpMeta = metaData;
        array = pickMemory(arrayLength - 12);
        metaData = pickMetadataMemory(arrayLength - 12);
        int count = 0;
        for (int i = 0; i < arrayLength; i++) {
            if (isValuable(tmpMeta, i)) {
                array[count] = tmpArray[i];
                count++;
            }
        }
        for (int i = 0; i < size; i++) {
            setMetadataValue(i, 1);
        }
        size = count;
        arrayLength -= 12;
        delete tmpArray;
        delete tmpMeta;
    }

    void reform() {
        bool prev = true;
        int count = 0;
        for (int i = 0; i < arrayLength; i++) {
            T cur = array[i];
            if (isValuable(metaData, i)) {
                if (i != 0) {
                    if (!prev) {
                        array[count] = cur;
                        prev = false;
                    }
                }
                count++;
            } else {
                prev = isValuable(metaData, i);
            }
        }
        delete metaData;
        metaData = pickMetadataMemory(arrayLength);
        for (int i = 0; i < count; i++) {
            setMetadataValue(i, 1);
        }
    }

    void increaseMemory() {
        T* tmpArray = array;
        byte* tmpMeta = metaData;
        arrayLength += 12;
        array = pickMemory(arrayLength);
        metaData = pickMetadataMemory(arrayLength);
        for (int i = 0; i < size; i++) {
            array[i] = tmpArray[i];
        }
        int mod = size % 8;
        int div = size / 8;
        int metaSize = div;
        if (mod != 0) {
            metaSize++;
        }
        for (int i = 0; i < metaSize; i++) {
            metaData[i] = tmpMeta[i];
        }
        delete tmpArray;
        delete tmpMeta;
    }

    T* pickMemory(const int size) {
        T* memory = new T[size];
        for (int i = 0; i < size; i++) {
            memory[i] = NULL;
        }
        return memory;
    }

    bool isValuable(const byte* byteArray, const int pos) {
        byte datByte = getByte(byteArray, pos);
        byte mask = 1 << (pos % 8);
        return (mask & datByte);
    }

    byte getByte(const byte* byteArray, const int pos) {
        int div = pos / 8;
        return byteArray[div];
    }

    void setMetadataValue(const int pos, const int value) {
        int mod = pos % 8;
        int div = pos / 8;
        byte m = metaData[div];
        if (value == 0) {
            m = ~(1 << mod) & m;
        } else {
            m = 1 << mod | m;
        }
        metaData[div] = m;
    }

    byte* pickMetadataMemory(const int arraySize) {
        int mod = arraySize % 8;
        int div = arraySize / 8;
        int size = div;
        if (mod != 0) {
            size++;
        }
        byte* meta = new byte[size];
        for (int i = 0; i < size; i++) {
            meta[i] = 0;
        }
        return meta;
    }
};

#endif // ARRAYVECTOR_H
