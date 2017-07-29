
#ifndef RHdriver_h
#define RHdeiver_h

#include "RadioHead.h"

class RHdriver
{
public:
  typedef enum
  {
    RHModeInitialising = 0, ///< Transport is initialising. Initial default value until init() is called..
	  RHModeSleep,            ///< Transport hardware is in low power sleep mode (if supported)
	  RHModeIdle,             ///< Transport is idle.
	  RHModeTx,               ///< Transport is in the process of transmitting a message.
	  RHModeRx                ///< Transport is in the process of receiving a message.
 }RHMode;
 RHdriver();
 virtual bool init();
 virtual bool available()=0;
 virtual bool recv(uint8_t *buff, uint8_t *len)=0;
 virtual bool send(const uint8_t *data, uint8_t len)=0;
 virtual uint8_t maxMessageLength()=0;
 virtual void waitAvailable();
 virtual bool waitAvailableTimeout(uint16_t timeout);
 virtual bool waitPacketSent(uint16_t timeout);
 virtual bool waitPacketSent();
 virtual void setThisAddress(uint8_t thisAddress);
 virtual void setHeaderTo(uint8_t to);
 virtual void setHeaderFrom(uint8_t from);
 virtual void setHeaderId(uint8_t id);
 virtual void setHeaderFlags(uint8_t set, uint8_t clear);
 virtual void setPromiscuous(bool promiscuous);
 uint8_t headerTo();
 uint8_t headerFrom();
 uint8_t headerId();
 uint8_t headerFlags();
 int8_t lastRssi();
 RHMode mode();
 void setMode(RHMode mode);
 virtual bool sleep();
 static void printBuffer(const char* prompt, const uint8_t* buff, uint8_t len);
 uint16_t rxBad();
 uint16_t rxGood();
 uint16_t txGood();

 protected:
   volatile RHMode _mode;
   uint8_t _thisAddress;
   bool _promiscuous;
   volatile uint8_t _rxHeaderTo;
   volatile uint8_t _rxHeaderFrom;
   volatile uint8_t _rxHeaderId;
   volatile uint8_t _rxHeaderFlags;
   uint8_t _txHeaderTo;
   uint8_t _txHeaderFrom;
   uint8_t _txHeaderFlags;
   uint8_t _txHeaderId;
   volatile int8_t _lastRssi;
   volatile int16_t _rxBad;
   volatile int16_t _rxGood;
   volatile int16_t _txGood;
 };

#endif 
