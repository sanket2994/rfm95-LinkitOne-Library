#ifndef RHspi_h
#define RHspi_h


#include "RadioHead.h"
#include "RHdriver.h"
#define RH_SPI_WRITE_MASK 0x80

class RHspi:public RHdriver
{
      public:
        //for clock division of spi
        typedef enum
        {
          Frequency1MHz=0,
          Frequency2MHz,
          Frequency4MHz,
          Frequency8MHz,
          Frequency16MHz
        }Frequency;

        typedef enum
        {
          DataMode0 =SPI_MODE0,
          DataMode1 = SPI_MODE1,
          DataMode2 = SPI_MODE2,
          DataMode3 = SPI_MODE3
        }DataMode;

        RHspi(uint8_t slaveSelectPin=10, Frequency frequency = Frequency1MHz, BitOrder bitOrder=MSBFIRST , DataMode dataMode = DataMode0);
        bool init();
        void begin();
        uint8_t spiRead(uint8_t reg);
        uint8_t spiWrite(uint8_t reg ,uint8_t val);
        uint8_t spiBurstRead(uint8_t reg, uint8_t *dest,uint8_t len);
        uint8_t spiBurstWrite(uint8_t reg, const uint8_t* src, uint8_t len);
        uint8_t digitalPinToInterrupt(uint8_t pin);
        //void setSlaveSelectPin(slaveSelectPin);
        //void attachInterrupt();
        //void detachInterrupt();
      protected:
        uint8_t _slaveSelectPin;
        Frequency _frequency;
        BitOrder _bitOrder;
        DataMode _dataMode;
};


#endif
