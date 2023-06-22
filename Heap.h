#pragma once
#include <iostream>

#include "PrioritizedQueue.h"
#include "Router.h"
using namespace std;

class Heap {
 public:
  // Constructor and destrucor
  Heap();
  ~Heap();

  // Sort the routerHeap vector as a heap
  void Heapify(vector<PrioritizedQueue*>& heap, int size, int i);

  // Adds new nodes to the heap and stores new packets in designated queues
  void AddToHeap(FakeIPPacket* pkt, int priority);

  // Remove a PQ node and dealocate memory
  void RemoveFromHeap(PrioritizedQueue* priorityQueueNode);

  // Check if routerHeap is not empty
  bool NotEmpty();

  // Return the size of the heap
  int getSizeOfHeap();

  // Return the node at index i in the routerHeap
  PrioritizedQueue* getQueueAt(int i);

 private:
  // Stores PrioritizedQueue as a heap
  vector<PrioritizedQueue*> routerHeap;
};