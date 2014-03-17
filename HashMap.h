#ifndef HASHMAP_H
#define HASHMAP_H

#include "Iterator.h"

namespace containers {

template <class K, class V> class HashMap {

public:

    HashMap() {
        hashTable = NULL;
    }

    class Entry {
    public:
        Entry(const K key, const V value):key(key),value(value) {
            next = NULL;
        }

        Entry* next;
        K key;
        V value;
    };

    class EntryList {
    public:
        EntryList() {
            after = NULL;
            first = NULL;
        }

        Entry* first;
        size_t hash;
        EntryList* after;
    };

    void put(const K& key, const V& data) {
        size_t hash = hashCode(key);
        EntryList* entryList = getEntryListForHash(hash);
        if (entryList != NULL) {
            for (Entry* en = entryList->first; en != NULL; en = en->next) {
                if (en->key == key) {
                    en->value = data;
                    return;
                }
            }
            Entry* entry = new Entry(key, data);
            entry->next = entryList->first;
            entryList->first = entry;
        } else {
            EntryList* newEntryList = new EntryList();
            newEntryList->hash = hash;
            Entry* entry = new Entry(key, data);
            newEntryList->first = entry;
            newEntryList->after = hashTable;
            hashTable = newEntryList;
        }
    }

    V get(const K& key) {
        size_t hash = hashCode(key);
        EntryList* entryList = getEntryListForHash(hash);
        if (entryList != NULL) {
            for (Entry* en = entryList->first; en != NULL; en = en->next) {
                if (en->key == key) {
                    return en->value;
                }
            }
        }
        return NULL; //what if V == int|float|etc?
    }

    V remove(const K& key) {
        size_t hash = hashCode(key);
        V returnValue = NULL;
        EntryList* entryList = getEntryListForHash(hash);
        if (entryList != NULL) {
            Entry* prev = entryList->first;
            for (Entry* en = entryList->first; en != NULL; en = en->next) {
                if (en->key == key) {
                    if (en == prev) { //so "en" is "first"
                        entryList->first = en->next;
                    } else {
                        prev->next = en->next;
                    }
                    returnValue = en->value;
                    delete en;
                    break;
                }
                prev = en;
            }
            if (entryList->first == NULL) {
                removeEntryListWithHash(hash);
            }
        }
        return returnValue;
    }

    ~HashMap() {
        EntryList* el = hashTable;
        while (el != NULL) {
            EntryList* after = el->after;
            Entry* en = el->first;
            while (en != NULL) {
                Entry* next = en->next;
                delete en;
                en = next;
            }
            delete el;
            el = after;
        }
    }

    class MapIterator : public Iterator<V> {
    public:

        MapIterator(EntryList* hashTable) {
            curEntryList = hashTable;
            curEntry = hashTable->first;
        }

        V next() {
            if (curEntry == NULL) {
                return NULL;
            }
            if (curEntry->next == NULL) {
                if (curEntryList->after == NULL) {
                    return NULL;
                }
                curEntryList = curEntryList->after;
                curEntry = curEntryList->first;
            } else {
                curEntry = curEntry->next;
            }
            return curEntry->value;
        }

        bool hasNext() {
            bool has = false;
            if (curEntry != NULL && curEntry->next != NULL) {
                has = true;
            } else if (curEntryList != NULL && curEntryList->after != NULL) {
                has = true;
            }
            return has;
        }

        V current() {
            if (curEntry == NULL) {
                return NULL;
            }
            return curEntry->value;
        }

    private:
        EntryList* curEntryList;
        Entry* curEntry;
    };

    Iterator<V>*  iterator() {
        return new MapIterator(hashTable);
    }

private:
    EntryList* hashTable;

    EntryList* getEntryListForHash(const size_t hash) {
        for (EntryList* curList = hashTable; curList != NULL; curList = curList->after) {
            if (curList != NULL && curList->hash == hash) {
                return curList;
            }
        }
        return NULL;
    }

    void removeEntryListWithHash(const size_t hash) {
        EntryList* prev = hashTable;
        for (EntryList* curList = hashTable; curList != NULL; curList = curList->after) {
            if (curList != NULL && curList->hash == hash) {
                if (hashTable == curList) {
                    hashTable = curList->after;
                } else {
                    prev->after = curList->after;
                }
                delete curList;
                break;
            }
            prev = curList;
        }
    }

};

template <class K>
size_t hashCode(const K& key);

//basic specifications

template <> size_t hashCode<QString>(const QString& key) {
    size_t hash = 0;
    for (int i = 0; i < key.length(); i++) {
        QChar c = key.at(i);
        hash = hash * 31 + c.toAscii();
    }
    return hash;
}

} //containers


#endif // HASHMAP_H
