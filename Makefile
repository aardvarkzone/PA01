# Makefile
CXX = g++

CXXFLAGS = -std=c++11

game: cards.cpp main.cpp cards.h utility.cpp utility.h
		g++ --std=c++11 -Wall cards.cpp main.cpp utility.cpp -o game
tests: cards.cpp main.cpp cards.h 
		g++ --std=c++11 -Wall cards.cpp main.cpp tests.cpp -o tests