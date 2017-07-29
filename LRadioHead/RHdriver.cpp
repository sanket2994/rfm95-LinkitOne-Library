
#include "RHdriver.h"

RHdriver::RHdriver()
    :
    _mode(RHModeInitialising),
    _thisAddress(RH_BROADCAST_ADDRESS),
    _txHeaderTo(RH_BROADCAST_ADDRESS),
    _txHeaderFrom(RH_BROADCAST_ADDRESS),
    _txHeaderId(0),
    _txHeaderFlags(0),
    _rxBad(0),
    _rxGood(0),
    _txGood(0)
{
}

bool RHdriver::init()
{
    return true;
}

void RHdriver::waitAvailable()
{
    while (!available())
	YIELD;
}


bool RHdriver::waitAvailableTimeout(uint16_t timeout)
{
    unsigned long starttime = millis();
    while ((millis() - starttime) < timeout)
    {
        if (available())
	{
           return true;
	}
	YIELD;
    }
    return false;
}


bool RHdriver::waitPacketSent()
{
    while (_mode == RHModeTx)
	YIELD; // Wait for any previous transmit to finish
    return true;
}

bool RHdriver::waitPacketSent(uint16_t timeout)
{
    unsigned long starttime = millis();
    while ((millis() - starttime) < timeout)
    {
        if (_mode != RHModeTx) // Any previous transmit finished?
           return true;
	YIELD;
    }
    return false;
}


void RHdriver::setPromiscuous(bool promiscuous)
{
    _promiscuous = promiscuous;
}

void RHdriver::setThisAddress(uint8_t address)
{
    _thisAddress = address;
}

void RHdriver::setHeaderTo(uint8_t to)
{
    _txHeaderTo = to;
}

void RHdriver::setHeaderFrom(uint8_t from)
{
    _txHeaderFrom = from;
}

void RHdriver::setHeaderId(uint8_t id)
{
    _txHeaderId = id;
}


void RHdriver::setHeaderFlags(uint8_t set, uint8_t clear)
{
    _txHeaderFlags &= ~clear;
    _txHeaderFlags |= set;
}

uint8_t RHdriver::headerTo()
{
    return _rxHeaderTo;
}

uint8_t RHdriver::headerFrom()
{
    return _rxHeaderFrom;
}

uint8_t RHdriver::headerId()
{
    return _rxHeaderId;
}

uint8_t RHdriver::headerFlags()
{
    return _rxHeaderFlags;
}

int8_t RHdriver::lastRssi()
{
    return _lastRssi;
}

RHdriver::RHMode  RHdriver::mode()
{
    return _mode;
}

void  RHdriver::setMode(RHMode mode)
{
    _mode = mode;
}

bool  RHdriver::sleep()
{
    return false;
}

// Diagnostic help
void RHdriver::printBuffer(const char* prompt, const uint8_t* buf, uint8_t len)
{
    uint8_t i;

#ifdef RH_HAVE_SERIAL
    Serial.println(prompt);
    for (i = 0; i < len; i++)
    {
	if (i % 16 == 15)
	    Serial.println(buf[i], HEX);
	else
	{
	    Serial.print(buf[i], HEX);
	    Serial.print(' ');
	}
    }
    Serial.println("");
#endif
}

uint16_t RHdriver::rxBad()
{
    return _rxBad;
}

uint16_t RHdriver::rxGood()
{
    return _rxGood;
}

uint16_t RHdriver::txGood()
{
    return _txGood;
}
