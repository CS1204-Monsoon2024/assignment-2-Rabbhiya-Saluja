default: main

main: main.cpp HashTable.cpp
	g++ -o main main.cpp HashTable.cpp

clean:
	rm -f main
