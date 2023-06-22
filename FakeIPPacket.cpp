#include "FakeIPPacket.h"
FakeIPPacket::FakeIPPacket() {
  TOS = 0;
  length = 0;
  time = 0;
}

FakeIPPacket::FakeIPPacket(unsigned char tos, unsigned short l,
                           unsigned short t) {
  TOS = tos;
  length = l;
  time = t;
}

void FakeIPPacket::AssignTOS(unsigned short tos) { TOS = tos; };
void FakeIPPacket::AssignLength(unsigned short l) { length = l; };
void FakeIPPacket::AssignTime(unsigned short t) { time = t; };
unsigned char FakeIPPacket::GetTOS() { return TOS; };
unsigned short FakeIPPacket::GetLength() { return length; };
unsigned short FakeIPPacket::GetTime() { return time; };
