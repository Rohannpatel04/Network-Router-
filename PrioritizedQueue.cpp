#include "PrioritizedQueue.h"

// Constructor for the PrioritizedQueue Obejct
PrioritizedQueue::PrioritizedQueue() {}

// Destructor for the PrioritizedQueue object
PrioritizedQueue::~PrioritizedQueue() {}

// Set the priority of a PrioritizedQueue
void PrioritizedQueue::setPriority(int updatedPriority) {
  // Sets priority to be the updated priority integer
  priority = updatedPriority;
}

// Returns the priority of a PrioritizedQueue
int PrioritizedQueue::getPriority() { return priority; }

// Adds a IP Packet to the PrioritizedQueue queue
void PrioritizedQueue::addIPPacket(FakeIPPacket* pkt) {
  // Adds pkt to the the back of the queue
  PQ.push(pkt);
}

// Removes the front packet from the queue
void PrioritizedQueue::removeIPPacket() {
  if (!PQ.empty()) {
    PQ.pop();
  }
}

// Check if the queue is empty
bool PrioritizedQueue::isEmpty() {
  if (PQ.empty()) {
    return true;
  }

  return false;
}

// Gets the top element in the PrioritizedQueue queue
FakeIPPacket* PrioritizedQueue::getIPPacket() {
  // Stores the the packet that is at the front of the queue as Return Packet
  FakeIPPacket* returnPacket = PQ.front();

  return returnPacket;
}
