g++ -g -O0 NetworkSim.cpp Router.cpp PrioritizedQueue.cpp FakeIPPacket.cpp Heap.cpp -o netsim
valgrind --leak-check=yes ./netsim
./netsim
