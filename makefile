CC = gcc
CXX = g++ 

CFLAGS = -Wall -Wextra -std=c11
CXXFLAGS = -Wall -Wextra -std=c++17

all: vehicle_app

vehicle.o:	vehicle.c vehicle.h
    		$(CC) $(CFLAGS) -c vehicle.c -o vehicle.o

vehicle_test: test_vehicle.cpp vehicle.o
	$(CXX) $(CXXFLAGS) test_vehicle.cpp vehicle.o -lgtest -lgtest_main -pthread -o vehicle_test

test:	vehicle_test
		./vehicle_test

clean:
	rm -f *.o vehicle_test

.PHONY: all test clean