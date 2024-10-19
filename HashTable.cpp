#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int elementCount;
    const float loadFactorThreshold = 0.8;

    int hashFunction(int key) const {
        return key % size;
    }

    bool isPrime(int n) const {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int getNextPrime(int start) const {
        while (!isPrime(start)) {
            start++;
        }
        return start;
    }

    void resizeTable() {
        int newSize = getNextPrime(size * 2);
        std::vector<int> newTable(newSize, -1);
        for (int i = 0; i < size; i++) {
            if (table[i] != -1) {
                int newHash = hashFunction(table[i]);
                int j = 0;
                while (newTable[(newHash + j * j) % newSize] != -1) {
                    j++;
                }
                newTable[(newHash + j * j) % newSize] = table[i];
            }
        }
        table = std::move(newTable);
        size = newSize;
    }

public:
    HashTable(int initialSize) : size(getNextPrime(initialSize)), elementCount(0) {
        table.resize(size, -1);
    }

    // Copy constructor
    HashTable(const HashTable& other)
        : table(other.table), size(other.size), elementCount(other.elementCount) {}

    // Move constructor
    HashTable(HashTable&& other) noexcept
        : table(std::move(other.table)), size(other.size), elementCount(other.elementCount) {
        other.size = 0; // Invalidate the other hash table
        other.elementCount = 0;
    }

    // Copy assignment operator
    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            table = other.table;
            size = other.size;
            elementCount = other.elementCount;
        }
        return *this;
    }

    // Move assignment operator
    HashTable& operator=(HashTable&& other) noexcept {
        if (this != &other) {
            table = std::move(other.table);
            size = other.size;
            elementCount = other.elementCount;

            other.size = 0; // Invalidate the other hash table
            other.elementCount = 0;
        }
        return *this;
    }

    void insert(int key) {
        if (elementCount >= size * loadFactorThreshold) {
            resizeTable();
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
                break;
            }
            i++;
        }
        std::cout << "Element not found\n";
    }

    int search(int key) const {
        int hash = hashFunction(key);
        int i = 0;

        while (i < size) {
            int pos = (hash + i * i) % size;
            if (table[pos] == key) {
                return pos;
            } else if (table[pos] == -1) {
                return -1;
            }
            i++;
        }
        return -1;
    }

    void printTable() const {
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
