Name: Rohan Patel 
Date: 2/3/23
Course: CSS343 B
Assignment: Assignment 2 - Router

Overview: 

- In this assighment I recreated a router
- Using the data structure of a heap to implement a priority queue for packets to flow through 

Compiled With: 

g++ -g -O0 NetworkSim.cpp Router.cpp PrioritizedQueue.cpp FakeIPPacket.cpp Heap.cpp -o netsim
valgrind --leak-check=yes ./netsim
./netsim