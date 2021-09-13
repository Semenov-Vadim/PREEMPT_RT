all: main

main: threads.cpp
	g++ -pthread -o threads threads.cpp

clean:
	rm -rf threads
