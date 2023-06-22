#pragma once
#include <iostream>
#include <queue>
#include <unordered_map>

#include "FakeIPPacket.h"
#include "Heap.h"
#include "PrioritizedQueue.h"
using namespace std;
struct Heap;

// This class is created to execute router like fucntions
class Router {
 public:
  // Constructor for the router object
  Router();

  // Destructor for the router object
  ~Router();

  // Adds a Packet to a deisgnated Prioritized Queue which is stored inside the
  // router heap
  void Enqueue(FakeIPPacket* pkt);

  // Removes the most prioritized FakeIPPacket from a Prioritized Queue from the
  // Router Heap
  FakeIPPacket* Dequeue(unsigned short time);

  // Prints statisics of the router
  void PrintStatistics();

  // Returns results
  vector<pair<FakeIPPacket*, unsigned short>> GetResults();

  bool NotEmpty();

 private:
  // Heap object
  Heap* heap;

  // Evalutes and returns the designated priority value depending on the
  // FakeIPPackets TOS
  int EvaluatePriority(FakeIPPacket* pkt);

  // vector of pairs to store a IP packet with the time it takes to go through
  // the router
  vector<pair<FakeIPPacket*, unsigned short>> results;
};
