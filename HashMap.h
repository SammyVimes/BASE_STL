#ifndef HASHMAP_H
#define HASHMAP_H

namespace containers {

template <class K, class V> class HashMap {

public:

    HashMap() {
        hashTable = hashTableLast = NULL;
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

        void remove(const K& key) {
            Entry* prev = first;
            for (Entry* en = first; en != NULL; en = en->next) {
                if (key == en->key) {
                    prev->next = en->next;
                    if (first == en) {
                        first = NULL;
                    }
                    delete en;
                    break;
                }
                prev = en;
            }
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
            if (hashTable == NULL) {
                hashTable = newEntryList;
                hashTableLast = hashTable;
            } else {
                hashTableLast->after = newEntryList;
                hashTableLast = hashTableLast->after;
            }
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
        return NULL; //А если V == int|float|etc?
    }

    void remove(const K key) {

    }

    ~HashMap() {
    }

private:
    EntryList* hashTableLast;
    EntryList* hashTable;


    EntryList* getEntryListForHash(const size_t hash) {
        for (EntryList* curList = hashTable; curList != NULL; curList = curList->after) {
            if (curList != NULL && curList->hash == hash) {
                return curList;
            }
        }
        return NULL;
    }

};

template <class K>
size_t hashCode(const K& key);

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
