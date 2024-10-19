default: main.cpp HashTable.cpp
    g++ -o main.out main.cpp HashTable.cpp

clean:
    rm -f .out

