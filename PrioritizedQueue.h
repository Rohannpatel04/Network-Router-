#pragma once
#include <iostream>
#include <queue>

#include "FakeIPPacket.h"

using namespace std;

// This class creates a PrioritizedQueue Object which will be stored inside the
// Router Heap
class PrioritizedQueue {
 public:
  // Constructor for the PrioritizedQueue Obejct
  PrioritizedQueue();
  // Destructor for the PrioritizedQueue object
  ~PrioritizedQueue();
  // Copy Constructor for PrioritizedQueue object
  PrioritizedQueue(PrioritizedQueue& p);

  // Set the priority of a PrioritizedQueue
  void setPriority(int updatedPriority);

  // Get the priority of a PrioritizedQueue
  int getPriority();

  // Adds a IP Packet to the PrioritizedQueue queue
  void addIPPacket(FakeIPPacket* pkt);

  // Gets the top element in the PrioritizedQueue queue
  FakeIPPacket* getIPPacket();

  // Removes the front packet from the queue
  void removeIPPacket();

  // Check if the queue is empty
  bool isEmpty();

 private:
  int priority;
  queue<FakeIPPacket*> PQ;
};