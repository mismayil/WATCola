#include "nameServer.h"
#include "printer.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
								prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents)
{
	vendingMachines = new VendingMachine*[numVendingMachines];
	vmstudentmap = new unsigned int[numStudents];

	for (unsigned int i = 0; i < numVendingMachines; i++) {
		vendingMachines[i] = NULL;
	}
}

NameServer::~NameServer() {
	delete [] vendingMachines;
	delete [] vmstudentmap;
}

void NameServer::VMregister(VendingMachine *vendingmachine) {
	unsigned int id = vendingmachine->getId();
	prt.print(Printer::NameServer, 'R', (int) id);									// DO PRINT IN MAIN
	vendingMachines[id] = vendingmachine;
}

VendingMachine *NameServer::getMachine(unsigned int id) {
	prt.print(Printer::NameServer, 'N', (int) id, (int) vmstudentmap[id]);			// DO PRINT IN MAIN
	VendingMachine *machine = vendingMachines[vmstudentmap[id]];
	vmstudentmap[id] = (vmstudentmap[id] + 1) % numVendingMachines;					// DO IN MAIN
	return machine;
}

VendingMachine **NameServer::getMachineList() {
	return vendingMachines;
}

void NameServer::main(){
	prt.print(Printer::NameServer, 'S');

	for (unsigned int i = 0; i < numStudents; i++) {
		vmstudentmap[i] = vendingMachines[i % numVendingMachines]->getId();
	}

	for(;;) {
		_Accept(~NameServer) { break; }

		// ADD more _Accept()'s'
	}

	prt.print(Printer::NameServer, 'F');
}
