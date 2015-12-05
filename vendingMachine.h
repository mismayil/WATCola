#ifndef __VendingMachine_H__
#define __VendingMachine_H__

#include "watcard.h"

_Monitor Printer;
_Task NameServer;


_Task VendingMachine {
	Printer &prt;
	NameServer &nameServer;
	unsigned int id;
	unsigned int sodaCost;
	unsigned int maxStockPerFlavour;

    void main();
  public:
    enum Flavours { berry, cherry };                 // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};


#endif