#include "bottlingPlant.h"
#include "vendingMachine.h"
#include "printer.h"
#include "truck.h"
#include "MPRNG.h"


BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                            unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                            unsigned int timeBetweenShipments) :
                            prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
                            maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
                            timeBetweenShipments(timeBetweenShipments)
{
    shipment = new unsigned int[VendingMachine::Flavours::NUM_FLAVOURS];
    closingDown = false;
}

BottlingPlant::~BottlingPlant() {
    delete [] shipment;
}

void BottlingPlant::getShipment(unsigned int cargo[]) {
    if (!closingDown) {
        for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) {
            cargo[i] = shipment[i];
        }
    }
}

void BottlingPlant::main() {
    prt.print(Printer::BottlingPlant, 'S');

    // create a truck
    Truck *truck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    for (;;) {
        unsigned int production = 0;
        for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) {
            unsigned int produce = mprnGen(0, maxShippedPerFlavour);
            shipment[i] = produce;
            production += produce;
        }

        prt.print(Printer::BottlingPlant, 'G', (int) production);

        _Accept(~BottlingPlant) {
            closingDown = true;
            _Accept(getShipment) {
                _Resume Shutdown() _At *truck;
            }
            delete truck;
            break;
        }
        or
        _Accept(getShipment) {
            prt.print(Printer::BottlingPlant, 'P');
            yield(timeBetweenShipments);
        }
    }

    prt.print(Printer::BottlingPlant, 'F');
}
