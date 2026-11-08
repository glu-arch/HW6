.PHONY: all clean

all: rbt-tests.exe rbt-tests-first.exe

rbt-tests.exe: RedBlackTree.h RedBlackTreeTests.cpp RedBlackTree.cpp
	g++ -std=c++11 -Wall -g RedBlackTreeTests.cpp RedBlackTree.cpp -o rbt-tests.exe

rbt-tests-first.exe: RedBlackTree.h RedBlackTreeTestsFirstStep.cpp RedBlackTree.cpp
	g++ -std=c++11 -Wall -g RedBlackTreeTestsFirstStep.cpp RedBlackTree.cpp -o rbt-tests-first.exe


clean:
	rm -f rbt-tests.exe rbt-tests-first.exe
