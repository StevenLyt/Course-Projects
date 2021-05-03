CXX = g++
CXXFLAGS = -g -Wall -std=c++11

all: counting

counting: counting.cpp hashtable.o
	$(CXX) $(CXXFLAGS) $^ -o $@

hashtable.o: hashtable.cpp hashtable.h
	$(CXX) $(CXXFLAGS) -c $< -o $@