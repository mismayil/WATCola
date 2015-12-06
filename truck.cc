#include "truck.h"
#include "MPRNG.h"
#include "nameServer.h"
#include "bottlingPlant.h"
#include "vendingMachine.h"
#include "printer.h"

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
            unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
            prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines),
            maxStockPerFlavour(maxStockPerFlavour) {}

Truck::~Truck() {}

void Truck::main() {
    prt.print(Printer::Truck, 'S');
    VendingMachine **machineList = nameServer.getMachineList();
    unsigned int cargo[VendingMachine::NUM_FLAVOURS];
    unsigned int lastMachine = 0;

    for (;;) {
        try {
            _Enable {
                yield(mprnGen(1, 10));
                plant.getShipment(cargo);
                unsigned int total = 0;

                for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) {
                    total += cargo[i];
                }

                prt.print(Printer::Truck, 'P', (int) total);

                for (unsigned int i = lastMachine; i < lastMachine + numVendingMachines; i++) {
                    VendingMachine *machine = machineList[i % numVendingMachines];
                    unsigned int *inventory = machine->inventory();
                    unsigned int notReplenished = 0;

                    prt.print(Printer::Truck, 'd', (int) machine->getId(), (int) total);

                    for (unsigned int j = 0; j < VendingMachine::NUM_FLAVOURS; j++) {
                        unsigned int demand = maxStockPerFlavour - inventory[j];
                        unsigned int supply = cargo[j] < demand ? cargo[j] : demand;
                        inventory[j] += supply;
                        cargo[j] -= supply;
                        total -= supply;
                        notReplenished += demand - supply;
                    }

                    prt.print(Printer::Truck, 'U', (int) machine->getId(), (int) notReplenished);

                    machine->restocked();

                    prt.print(Printer::Truck, 'D');

                    if (total == 0) {
                        lastMachine = (i + 1) % numVendingMachines;
                        break;
                    }
                }
            }
        } catch(BottlingPlant::Shutdown) {
            break;
        }
    }

    prt.print(Printer::Truck, 'F');
}
