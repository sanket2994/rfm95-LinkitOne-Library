
#include "LRHspi.h"

RHspi::RHspi(uint8_t slaveSelectPin , Frequency frequency, BitOrder bitOrder,
  DataMode dataMode) :
    _frequency(frequency),
    _bitOrder(bitOrder),
    _dataMode(dataMode),
    _slaveSelectPin(slaveSelectPin)
{
}
void RHspi::begin()
{
  uint8_t dataMode;
    if (_dataMode == DataMode0)
	dataMode = SPI_MODE0;
    else if (_dataMode == DataMode1)
	dataMode = SPI_MODE1;
    else if (_dataMode == DataMode2)
	dataMode = SPI_MODE2;
    else if (_dataMode == DataMode3)
	dataMode = SPI_MODE3;
    else
	dataMode = SPI_MODE0;

  SPI.begin();
  SPI.setDataMode(dataMode);

  BitOrder bitOrder;
  if(_bitOrder == MSBFIRST)
    bitOrder=MSBFIRST;
  else
    bitOrder=LSBFIRST;

  uint8_t divider;

  switch (_frequency) {
    case Frequency1MHz:
    default:
    #if F_CPU == 8000000
      divider = SPI_CLOCK_DIV8;
    #else
      divider = SPI_CLOCK_DIV16;
    #endif
    break;

    case Frequency2MHz:
      #if F_CPU == 8000000
	     divider = SPI_CLOCK_DIV4;
      #else
	     divider = SPI_CLOCK_DIV8;
      #endif
	    break;

    case Frequency4MHz:
    #if F_CPU == 8000000
      divider = SPI_CLOCK_DIV2;
    #else
      divider = SPI_CLOCK_DIV4;
    #endif
    break;

    case Frequency8MHz:
      divider = SPI_CLOCK_DIV2; // 4MHz on an 8MHz Arduino
	  break;

    case Frequency16MHz:
	    divider = SPI_CLOCK_DIV2; // Not really 16MHz, only 8MHz. 4MHz on an 8MHz Arduino
	    break;

  }
  //_divider=divider;
  SPI.begin();
  SPI.setClockDivider(divider);
}

bool RHspi::init()
{
  RHspi::begin();
  pinMode(_slaveSelectPin,OUTPUT);
  digitalWrite(_slaveSelectPin,HIGH);
  delay(100);
  return true;

}

uint8_t RHspi::spiRead(uint8_t reg)
{
  uint8_t val;
  ATOMIC_BLOCK_START;
  digitalWrite(_slaveSelectPin, LOW);
  SPI.transfer(reg & ~RH_SPI_WRITE_MASK);//address of the register to read from
  val=SPI.transfer(0);//shift register hence data gets swaped
  digitalWrite(_slaveSelectPin, HIGH);
  ATOMIC_BLOCK_END;
  return val;
}

uint8_t RHspi::spiWrite(uint8_t reg, uint8_t val)
{
  uint8_t status =0;
  ATOMIC_BLOCK_START;
  digitalWrite(_slaveSelectPin, LOW);
  status = SPI.transfer(reg | RH_SPI_WRITE_MASK); //address of the registerto write from
  SPI.transfer(val);
  digitalWrite(_slaveSelectPin,HIGH);
  ATOMIC_BLOCK_END;
  return status;
}

uint8_t RHspi::spiBurstRead(uint8_t reg, uint8_t *dest, uint8_t len)
{
  uint8_t status=0;
  ATOMIC_BLOCK_START;
  digitalWrite(_slaveSelectPin,LOW);
  status = SPI.transfer(reg & ~RH_SPI_WRITE_MASK);
  while(len--)
    *dest++=SPI.transfer(0);
  digitalWrite(_slaveSelectPin,HIGH);
  ATOMIC_BLOCK_END;
  return status;
}

uint8_t RHspi::spiBurstWrite(uint8_t reg, const uint8_t *src, uint8_t len)
{
  uint8_t status=0;
  ATOMIC_BLOCK_START;
  digitalWrite(_slaveSelectPin,LOW);
  status = SPI.transfer(reg | RH_SPI_WRITE_MASK );
  while(len--)
    SPI.transfer(*src++);
  digitalWrite(_slaveSelectPin, HIGH);
  ATOMIC_BLOCK_END;
  return status;
}

uint8_t RHspi::digitalPinToInterrupt(uint8_t pin)
{
  if(pin==2)
    return 0;
  else if(pin==3)
    return 1;
}

void RHspi::setSpiFrequency(Frequency frequency)
{
  _frequency =frequency;
}

void RHspi::setDataMode(DataMode dataMode)
{
  _dataMode=dataMode;
}

void RHspi::setBitOrder(BitOrder bitOrder)
{
  _bitOrder=bitOrder;
}
