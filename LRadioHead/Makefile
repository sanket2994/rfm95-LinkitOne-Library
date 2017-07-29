
CC= arm-linux-gnueabi-g++


archive: RH_RF95.o RHspi.o RHdriver.o 
	ar -crv libRadioHead.a RH_RF95.o RHspi.o RHdriver.o 	

RH_RF95.o:RHspi.o RHdriver.o 
	 $(CC) -c RH_RF95.cpp

RHspi.o: 
	$(CC) -c RHspi.cpp

RHdriver.o:
	$(CC) -c RHdriver.cpp




































