#include "vendingMachine.h"
#include "nameServer.h"
#include "printer.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    														unsigned int maxStockPerFlavour) :
								prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour)
{
    isRestocked = false;
    sodaInventory = new unsigned int[2];

    for (int i = 0; i < 2; i++) {
        sodaInventory = 0;
    }
}

VendingMachine::~VendingMachine() {
    delete [] sodaInventory;
}


void VendingMachine::buy(Flavours flavour, WATCard &card) {
    if (sodaInventory[flavour] == 0) _Throw Stock();
    if (card.getBalance() < sodaCost) _Throw Funds();
    card.withdraw(sodaCost);
}

unsigned int *VendingMachine::inventory() {
	return sodaInventory;
}

void VendingMachine::restocked(){
    isRestocked = true;
}

_Nomutex unsigned int VendingMachine::cost() {
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
	return id;
}

void VendingMachine::main() {

    for (;;) {
        _Accept(~VendingMachine) { break; }

    }
}
