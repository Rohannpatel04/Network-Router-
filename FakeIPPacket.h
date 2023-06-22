#pragma once
using namespace std;
#include <iostream>
class FakeIPPacket {
 public:
  FakeIPPacket();

  FakeIPPacket(unsigned char tos, unsigned short l, unsigned short t);

  void AssignTOS(unsigned short tos);
  void AssignLength(unsigned short l);
  void AssignTime(unsigned short t);
  unsigned char GetTOS();
  unsigned short GetLength();
  unsigned short GetTime();

 private:
  // see https://tools.ietf.org/html/rfc791#section-3.1 for details of a real IP
  // packet
  unsigned char TOS;
  unsigned short length;
  unsigned short time;
};