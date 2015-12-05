#include "vendingMachine.h"
#include "nameServer.h"
#include "printer.h"




VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    															unsigned int maxStockPerFlavour ) : 
								prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour){}



void VendingMachine::buy( Flavours flavour, WATCard &card ){
	(void) flavour;
	(void) card;
}


unsigned int *VendingMachine::inventory(){
	unsigned int a[1];
	a[0] = 5;

	return a;
}

void VendingMachine::restocked(){

}

_Nomutex unsigned int VendingMachine::cost(){
	return sodaCost;
}
_Nomutex unsigned int VendingMachine::getId(){
	return id;
}


void VendingMachine::main() {

}