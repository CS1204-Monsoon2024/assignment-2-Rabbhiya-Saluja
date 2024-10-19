
#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int count;
    const float loadFactorThreshold = 0.8;

    int hashFunction(int key) {
        return key % size;
    }

    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i <= std::sqrt(num); i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    int nextPrime(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    void resize() {
        int newSize = nextPrime(size * 2);
        std::vector<int> newTable(newSize, -1);
        for (int i = 0; i < size; i++) {
            if (table[i] != -1 && table[i] != -2) { 
                int key = table[i];
                int index = key % newSize;
                int j = 1;
                while (newTable[index] != -1) {
                    index = (key + j * j) % newSize;
                    j++;
                }
                newTable[index] = key;
            }
        }
        size = newSize;
        table = newTable;
    }

public:
    HashTable(int initialSize) {
        size = initialSize;
        table.resize(size, -1); 
        count = 0;
    }

    void insert(int key) {
        if (count / (float)size > loadFactorThreshold) {
            resize();
        }

        int index = hashFunction(key);
        int i = 0;
        while (table[index] != -1 && table[index] != -2) { 
            if (table[index] == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }
            i++;
            if (i >= size / 2) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
            index = (hashFunction(key) + i * i) % size;
        }
        table[index] = key;
        count++;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -2; 
                count--;
                return;
            }
            i++;
            if (i >= size / 2) break;
            index = (hashFunction(key) + i * i) % size;
        }
        std::cout << "Element not found" << std::endl;
    }

    int search(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (table[index] != -1) {
            if (table[index] == key) {
                return index;
            }
            i++;
            if (i >= size / 2) break;
            index = (hashFunction(key) + i * i) % size;
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else if (table[i] == -2) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
