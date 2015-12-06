#include "bank.h"


// Bank constructor
Bank::Bank( unsigned int numStudents ) : numStudents(numStudents){

	// each student’s account initially starts with a balance of $0.
	accounts = new unsigned int[numStudents];
	for (unsigned int i = 0; i < numStudents; i++){
		accounts[i] = 0;
	}

	couriers = new uCondition[numStudents];
}


// Bank destructor
Bank::~Bank(){
	delete[] accounts;
	delete[] couriers;
}	


// endows gifts to a specific student 
void Bank::deposit( unsigned int id, unsigned int amount ){
	accounts[id] += amount;
	couriers[id].signal();
}

// transfers money for a specific student.
void Bank::withdraw( unsigned int id, unsigned int amount ){

	// courier waits until enough money has been deposited
	while(accounts[id] < amount){
		couriers[id].wait();

		// call the next courier to do withdraw,
		// if there is one on the bench queue
		// if(!couriers[id].empty()){	
		// 	couriers[id].signal();
		// }
	}
	accounts[id] -= amount;
}

/* END */