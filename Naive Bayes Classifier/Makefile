CXX = g++
CXXFLAGS = -g -Wall -std=c++11

all: bayes

bayes: main.cpp bayes.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bayes.o: bayes.cpp bayes.h
	$(CXX) $(CXXFLAGS) -c $< -o $@