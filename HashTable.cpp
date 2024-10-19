#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int elementCount;
    const float loadFactorThreshold = 0.8;

    int hashFunction(int key) {
        return key % size;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int getNextPrime(int start) {
        while (!isPrime(start)) {
            start++;
        }
        return start;
    }

    void resizeTable() {
        int newSize = getNextPrime(size * 2);
        std::vector<int> newTable(newSize, -1); // Create new table
        for (int i = 0; i < size; i++) {
            if (table[i] != -1) {
                int newHash = table[i] % newSize;
                int j = 0;
                while (newTable[(newHash + j * j) % newSize] != -1) {
                    j++;
                }
                newTable[(newHash + j * j) % newSize] = table[i]; // Rehash element
            }
        }
        table = newTable;
        size = newSize;
    }

public:
    HashTable(int initialSize) : size(initialSize), elementCount(0) {
        table.resize(size, -1);  // Initialize the hash table
    }

    void insert(int key) {
        if (elementCount >= size * loadFactorThreshold) {
            resizeTable();  // Resize when load factor exceeds threshold
        }

        int hash = hashFunction(key);
        int i = 0;

        while (i < size) {
            int pos = (hash + i * i) % size;
            if (table[pos] == -1) {
                table[pos] = key;
                elementCount++;
                return;
            } else if (table[pos] == key) {
                std::cout << "Duplicate key insertion is not allowed\n";
                return;
            }
            i++;
        }
        std::cout << "Max probing limit reached!\n";
    }

    void remove(int key) {
        int hash = hashFunction(key);
        int i = 0;

        while (i < size) {
            int pos = (hash + i * i) % size;
            if (table[pos] == key) {
                table[pos] = -1;
                elementCount--;
                return;
            } else if (table[pos] == -1) {
                break;  // Stop if an empty slot is found
            }
            i++;
        }
        std::cout << "Element not found\n";
    }

    int search(int key) {
        int hash = hashFunction(key);
        int i = 0;

        while (i < size) {
            int pos = (hash + i * i) % size;
            if (table[pos] == key) {
                return pos;
            } else if (table[pos] == -1) {
                return -1;  // Stop if an empty slot is found
            }
            i++;
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
