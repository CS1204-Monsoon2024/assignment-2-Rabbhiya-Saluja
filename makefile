default: main.cpp HashTable.cpp
    g++ main.cpp HashTable.cpp -o main.out 

clean:
    rm -f main.out

