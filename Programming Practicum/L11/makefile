lab11: lab11Main.o lab11List.o
	g++ -o lab11 lab11Main.o lab11List.o

lab11Main.o: lab11Main.cpp lab11List.h
	g++ -c lab11Main.cpp

lab11List.o: lab11List.cpp lab11List.h
	g++ -c lab11List.cpp

clean:
	rm lab11*.o lab11
