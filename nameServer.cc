#include "nameServer.h"
#include "printer.h"




NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) :
								prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents){}


void NameServer::VMregister( VendingMachine *vendingmachine ){
	(void) vendingmachine;
}

VendingMachine *NameServer::getMachine( unsigned int id ){
	VendingMachine *v;
	v = new VendingMachine( prt, *this, id,  6, 9 );
	return v;
}

VendingMachine **NameServer::getMachineList(){
	VendingMachine *v[1];
	v[0] = new VendingMachine( prt, *this, 0,  6, 9 );
	return v;
}