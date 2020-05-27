CXX = g++
FLAGS = -std=c++17
INCLUDE = -I .
OPTIM = -O0 -g
WARN = -Wall -Wextra -pedantic
ALL = $(FLAGS) $(INCLUDE) $(OPTIM) $(WARN)

default:
	$(CXX) $(ALL) -c Scheduler/Database.hpp
	$(CXX) $(ALL) -c main.cpp
	$(CXX) -o main main.o -lsqlite3
	rm -f main.o Scheduler/*.gch

