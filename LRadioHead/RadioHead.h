#ifndef RadioHead_h
#define RadioHead_h


#include<Arduino.h>
#include<wiring.h>
#include<SPI.h>

 #define ATOMIC_BLOCK_START noInterrupts()
 #define ATOMIC_BLOCK_END   interrupts()

#define RH_BROADCAST_ADDRESS 0xff
#define RH_HAVE_HARDWARE_SPI
#define RH_HAVE_SERIAL
 #define YIELD


#endif
