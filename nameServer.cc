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
	vid = vendingmachine->getId();
	vendingMachines[vid] = vendingmachine;
}

VendingMachine *NameServer::getMachine(unsigned int id) {
	sid = id;
	VendingMachine *machine = vendingMachines[vmstudentmap[sid]];
	return machine;
}

VendingMachine **NameServer::getMachineList() {
	return vendingMachines;
}

void NameServer::main(){
	prt.print(Printer::NameServer, 'S');

	for (unsigned int i = 0; i < numStudents; i++) {
		vmstudentmap[i] = i % numVendingMachines;
	}

	for(;;) {

		_Accept(~NameServer) { break; }
		or
		_Accept(VMregister) {
			prt.print(Printer::NameServer, 'R', (int) vid);
		}
		or
		_Accept(getMachine) {
			vmstudentmap[sid] = (vmstudentmap[sid] + 1) % numVendingMachines;
			prt.print(Printer::NameServer, 'N', (int) sid, (int) vmstudentmap[sid]);
		}
		// or
		// _Accept(getMachineList)
	}

	prt.print(Printer::NameServer, 'F');
}
