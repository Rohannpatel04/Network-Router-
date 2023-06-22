#include "Heap.h"

// Constructor and destrucor
Heap::Heap() {}
Heap::~Heap() {}
// Sort the routerHeap vector as a MAX heap
void Heap::Heapify(vector<PrioritizedQueue*>& heap, int size, int i) {
  // Set the index of the root as largest
  int largest = i;
  // Set the index of the left child as left
  int left = 2 * i + 1;
  // Set the index of the right child as the right
  int right = 2 * i + 2;

  // If the left child priority is greater than the root
  if (left < size && heap[left]->getPriority() > heap[largest]->getPriority()) {
    // Set the largest to be the index of the left child
    largest = left;
  }

  // If the right child priority is greater than the root's priority
  if (right < size &&
      heap[right]->getPriority() > heap[largest]->getPriority()) {
    // Set the largest to be the index of the right child
    largest = right;
  }

  // if the largest is not the root
  if (!(largest == i)) {
    // swap the root and the largest
    swap(heap[largest], heap[i]);

    // Call heapify with the root(i) now being: largest
    Heapify(heap, size, largest);
  }
}

// Adds new nodes to the heap and stores new packets in designated queues
void Heap::AddToHeap(FakeIPPacket* pkt, int priority) {
  int x = 1;

  // Check if the heap contains the pkt's priority queue
  for (int i = 0; i < routerHeap.size(); i++) {
    // if the PQ node already exist add the packet to
    // the respective queue
    if (routerHeap[i]->getPriority() == priority) {
      routerHeap[i]->addIPPacket(pkt);
      x = 0;
      break;
    }
  }

  // If the heap does not contains the PQ node
  if (x == 1) {
    // Create a new PrioritizedQueue node which will store the new pkt
    PrioritizedQueue* PQ = new PrioritizedQueue();

    // assign a priority to the PQ node
    PQ->setPriority(priority);

    // Add the packet to the PQ node
    PQ->addIPPacket(pkt);

    // Add the PQ node to the heap
    routerHeap.push_back(PQ);

    // Call Heapify to prioritize the nodes

    Heapify(routerHeap, routerHeap.size(), 0);

    for (int i = 0; i < routerHeap.size(); i++) {
    }
  }
}

// Remove a PQ node and dealocate memory
void Heap::RemoveFromHeap(PrioritizedQueue* priorityQueueNode) {
  // Swamp the node that needs to be deleted with the last node in the heap

  if (!routerHeap.empty()) {
    swap(routerHeap[0], routerHeap[routerHeap.size() - 1]);
    routerHeap.pop_back();

    // Delete the node that is being passed in
    delete priorityQueueNode;

    // Restructure the heap to be prioritized again
    Heapify(routerHeap, routerHeap.size(), 0);
  }
}

// Check if routerHeap is not empty
bool Heap::NotEmpty() {
  if (!routerHeap.empty()) {
    return true;
  }
  return false;
}

// Return the node at index i in the routerHeap
int Heap::getSizeOfHeap() {
  int size = routerHeap.size();
  return size;
}
// Return the node at index i in the routerHeap
PrioritizedQueue* Heap::getQueueAt(int i) {
  PrioritizedQueue* PQ = routerHeap[i];
  return PQ;
}