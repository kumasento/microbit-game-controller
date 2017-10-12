/**
 * The main entry for the micro:bit game controller.
 */

#include <stdlib.h>
#include <string.h>

#include "MicroBit.h"

#define MAX_BUF_SZ 256

MicroBit uBit;

int main() {
  // stream buffer
  char buf[MAX_BUF_SZ];
  // connected to USB serial ports
  MicroBitSerial serial(USBTX, USBRX);
  // accelerometer
  int X, Y, Z;

  uBit.init();

  // uBit.display.scroll("GAME CONTROLLER!");


  while (true) {
    // access accelerometer
    X = uBit.accelerometer.getX();
    Y = uBit.accelerometer.getY();
    Z = uBit.accelerometer.getZ();

    sprintf(buf, "x%dy%dz%d\n", X, Y, Z);

    ManagedString s((const char *) buf);
  
    serial.send(s, SYNC_SPINWAIT);
  }

  release_fiber();

  return 0;
}
