#include "Router.h"

#include <cmath>
#include <iostream>

using namespace std;

// Constructor for the router object
Router::Router() { heap = new Heap(); }

// Destructor for the router object
Router::~Router() {
  // iterate through the vector of pairs and dealocate
  // memory
  for (int i = 0; i < results.size(); i++) {
    delete results[i].first;
    results[i].first = NULL;
  }

  // Delete nodes in heap
  for (int i = 0; i < heap->getSizeOfHeap(); i++) {
    delete heap->getQueueAt(i);
  }

  // Delete heap
  delete heap;
}

// Adds a Packet to a deisgnated Prioritized Queue which is stored inside the
// router heap
void Router::Enqueue(FakeIPPacket* pkt) {
  // Adds the incoming packet into the priority queue which is implemented as a
  // heap
  heap->AddToHeap(pkt, EvaluatePriority(pkt));
}

// Removes the most prioritized FakeIPPacket from a Prioritized Queue from the
// Router Heap
FakeIPPacket* Router::Dequeue(unsigned short time) {
  if (heap->NotEmpty()) {
    // Calculate and save the time and add the packet and time into the
    // results vector

    unsigned short t = time - heap->getQueueAt(0)->getIPPacket()->GetTime();
    results.push_back(make_pair(heap->getQueueAt(0)->getIPPacket(), t));
  }

  // save the dequeued packet as a varible so we can return it.
  FakeIPPacket* dequeuedPacket = heap->getQueueAt(0)->getIPPacket();

  // Pop the top pkt within the first index of the router heap queue
  heap->getQueueAt(0)->removeIPPacket();

  // If the PQ node queue is empty there is no need of it in the heap so this
  // will remove it
  if (heap->getQueueAt(0)->isEmpty()) {
    heap->RemoveFromHeap(heap->getQueueAt(0));
  }

  return dequeuedPacket;
}

// Prints statisics of the router
void Router::PrintStatistics() {
  // Total variables
  double totalMean = 0;
  double totalStd = 0;
  double totalTime = 0;
  double totalCount = 0;

  // The time and count of packets for the priorities are stored in this
  unordered_map<int, pair<double, double>> timeCount;

  // The min and max of packets for the priorities are stored in this map
  unordered_map<int, pair<double, double>> minMax;

  // Added priority levels as keys and default values
  timeCount.emplace(2, make_pair(0, 0));
  timeCount.emplace(1, make_pair(0, 0));
  timeCount.emplace(3, make_pair(0, 0));

  // Added priority levels as keys and default values
  minMax.emplace(2, make_pair(-1, 0));
  minMax.emplace(1, make_pair(-1, 0));
  minMax.emplace(3, make_pair(-1, 0));

  // Check the priority of thr packet and add the packet time and
  // apearences
  // to the map
  for (int i = 0; i < results.size(); i++) {
    int p = EvaluatePriority(results[i].first);

    double t1 = timeCount.at(p).first;
    double t2 = results[i].second;
    // Add the time of the packet to the map
    timeCount.at(p).first = t1 + t2;

    // Add the apearence to the map
    timeCount.at(p).second += 1;

    // Compare the time to the max time
    double tMAX = minMax.at(p).second;

    //  If the time is greater than the max time replace
    if (tMAX < t2) {
      minMax.at(p).second = t2;
    }

    // Compare the time to the min time
    double tMIN = minMax.at(p).first;

    // To set the first min values
    if (minMax.at(p).first == -1) {
      minMax.at(p).first = t2;
    }

    // if the time is less than the min time replace it in the map
    else if (tMIN > t2) {
      minMax.at(p).first = t2;
    }
    // Add the data to the the total varibles too
    double c = 1;
    totalCount += c;
    totalTime += t2;
  }

  cout << " " << endl;
  cout << "_____________MEDIAN & STANDARD DEVIATION_____________" << endl;
  // Iterate through the timeCount map and calculate the mean and std and
  // print them out
  for (auto i = timeCount.begin(); i != timeCount.end(); i++) {
    cout << " " << endl;
    double pMean = i->second.first / i->second.second;
    double pStd = 0;
    int priority = i->first;
    double counter = 0;

    // Find the STD
    for (int i = 0; i < totalCount; i++) {
      if (EvaluatePriority(results[i].first) == priority) {
        counter++;
        pStd += pow(results[i].first->GetTime() - pMean, 2);
        pStd = sqrt(pStd / counter);
      }
    }

    // print out the mean and std
    cout << "Priortity " << priority << ":" << endl;
    cout << "Mean: " << pMean << endl;
    cout << "STD: " << pStd << endl;
  }

  cout << " " << endl;
  cout << "_____________MIN & MAX_____________" << endl;
  // Iterate through the maxMin map and print out the max and min for
  // each of the priorities
  for (auto i = minMax.begin(); i != minMax.end(); i++) {
    cout << " " << endl;
    double MIN = i->second.first;
    double MAX = i->second.second;
    int Priority = i->first;

    // Print out the min and max values
    cout << "Priority " << Priority << ":" << endl;
    cout << "Min Time : " << MIN << endl;
    cout << "Max Time : " << MAX << endl;
  }

  // Calculate the Mean for all the packets
  totalMean = totalTime / totalCount;

  // Calculate STD for all the packets
  for (int i = 0; i < totalCount; i++) {
    totalStd += pow(results[i].first->GetTime() - totalMean, 2);
    totalStd = sqrt(totalStd / totalCount);
  }

  cout << " " << endl;
  cout << "_____________TOTAL STATS_____________" << endl;
  cout << " " << endl;
  // Print out the totals
  cout << "Total Count: " << totalCount << endl;
  cout << "Total Time: " << totalTime << endl;
  cout << "Total Mean: " << totalMean << endl;
  cout << "Total STD: " << totalStd << endl;
}

// returns the vectors of pairs
vector<pair<FakeIPPacket*, unsigned short>> Router::GetResults() {
  return results;
}

bool Router::NotEmpty() {
  if (heap->NotEmpty()) {
    return true;
  }
  return false;
}

// Evalutes and returns the designated priority value depending on the
// FakeIPPacket specs
int Router::EvaluatePriority(FakeIPPacket* pkt) {
  int PointCounter = 0;

  // if the tos is greater than 170
  if (pkt->GetTOS() >= 170) {
    PointCounter += 30;
  }

  // if the tos is between 85 and 170
  if (pkt->GetTOS() < 170 && pkt->GetTOS() >= 85) {
    PointCounter += 20;
  }

  // if the tos is between 0 and 85
  if (pkt->GetTOS() < 85 && pkt->GetTOS() >= 0) {
    PointCounter += 10;
  }

  // if the length is less than or equal to 21845
  if (pkt->GetLength() <= 21845) {
    PointCounter += 30;
  }

  // if the length is greater than 21845 and less than or equal to 43690
  if (pkt->GetLength() > 21845 && pkt->GetLength() <= 43690) {
    PointCounter += 20;
  }

  // if  the length is greater than 43690
  if (pkt->GetLength() > 43690) {
    PointCounter += 10;
  }

  if (PointCounter > 40) {
    return 3;
  }

  if (PointCounter <= 40 && PointCounter > 20) {
    return 2;
  }

  if (PointCounter <= 20) {
    return 1;
  }

  return 0;
}
