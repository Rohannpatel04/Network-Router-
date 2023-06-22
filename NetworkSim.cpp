#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "FakeIPPacket.h"
#include "Router.h"
#define MAX_PACKETS 5
#define TIME_TO_RUN 1000

using namespace std;

float EvaluatePerformance(vector<pair<FakeIPPacket*, unsigned short>> results) {
  float score = 0.0;
  for (pair<FakeIPPacket*, unsigned short> r : results) {
    score += r.first->GetTOS() * r.first->GetLength() / (r.second + 1);
  }
  score = score / results.size();
  return score;
}

int main() {
  srand((unsigned)time(0));

  unsigned short t = 0;
  Router router;
  //	while (router.NotEmpty() || t < TIME_TO_RUN) {  // run until there are
  // no more packets left
  for (t = 0; t < TIME_TO_RUN; t++) {  // packet generator Time loop
    unsigned int numPackets = rand() % MAX_PACKETS;

    for (unsigned int i = 0; i < numPackets; i++) {  // packet generator loop
      // generate packet
      FakeIPPacket* pkt = new FakeIPPacket();
      pkt->AssignTOS(rand() % 256);
      pkt->AssignLength(rand() % 65535 + 1);
      pkt->AssignTime(t);
      // Enqueue packet
      router.Enqueue(pkt);
    }
    // Dequeue packet, 1 per second
    if (t != 0) {  // don't dequeue the first time step
      router.Dequeue(t);
    }
  }
  while (router.NotEmpty() && t >= TIME_TO_RUN) {
    t++;
    router.Dequeue(t);
  }
  //	}
  router.PrintStatistics();
  cout << endl
       << "Router Score: " << EvaluatePerformance(router.GetResults()) << endl;
}
