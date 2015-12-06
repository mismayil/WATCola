#include "vendingMachine.h"
#include "nameServer.h"
#include "printer.h"
#include <iostream>

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    														unsigned int maxStockPerFlavour) :
								prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour)
{
    isRestocked = false;
    ExceptionStock = false;
    ExceptionFunds = false;
    student = NULL;
    sodaInventory = new unsigned int[NUM_FLAVOURS];

    for (int i = 0; i < NUM_FLAVOURS; i++) {
        sodaInventory[i] = 0;
    }
}

VendingMachine::~VendingMachine() {
    delete [] sodaInventory;
}

void VendingMachine::buy(Flavours flavour, WATCard &card) {
    student = &uThisTask();
    if (sodaInventory[flavour] == 0) ExceptionStock = true;
    else if (card.getBalance() < sodaCost) ExceptionFunds = true;
    else {
        card.withdraw(sodaCost);
        sodaInventory[flavour]--;
        flavourRequested = flavour;
    }
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
    prt.print(Printer::Vending, (int) id, 'S', (int) sodaCost);

    nameServer.VMregister(this);

    for (;;) {
        try {
            _Accept(~VendingMachine) { break; }
            or
            _When(isRestocked) _Accept(buy) {
                if (ExceptionStock) {
                    _Resume Stock() _At *student;
                    ExceptionStock = false;
                }
                else
                if (ExceptionFunds) {
                    _Resume Funds() _At *student;
                    ExceptionFunds = false;
                }
                else prt.print(Printer::Vending, (int) id, 'B', (int) flavourRequested, sodaInventory[flavourRequested]);
            }
            or
            _Accept(inventory) {
                prt.print(Printer::Vending, (int) id, 'r');
            }
            or
            _Accept(restocked) {
                prt.print(Printer::Vending, (int) id, 'R');
            }

            unsigned int demand = 0;
            for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
                if (sodaInventory[i] == 0) demand++;
            }

            if (demand == NUM_FLAVOURS) isRestocked = false;
        } catch(uMutexFailure::RendezvousFailure) {
            std::cout << "RENDEZVOUS" << std::endl;
        }
    }

    prt.print(Printer::Vending, (int) id, 'F');
}
