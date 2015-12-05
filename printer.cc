#include <iostream>
#include "printer.h"

using namespace std;

// Constructor for Private struct defined in
// Printer class
Printer::info::info(){
	overwrite = false;
}


// default constructor
Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
 							numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers){

  cout << "Parent\tGropoff\tWATOff\tNames\tTruck\tPlant";

  for (unsigned int i = 0; i < numStudents; i++){
  	cout << "\tStud" << i;
  }

  for (unsigned int i = 0; i < numVendingMachines; i++){
  	cout << "\tMach" << i;
  }

  for (unsigned int i = 0; i < numCouriers; i++){
  	cout << "\tCour" << i;
  }

  cout << endl;

  total = 6 + numStudents + numCouriers + numVendingMachines;

  for (unsigned int i = 0; i < total; i++){
  	cout << "*******\t";
  }

  cout << endl;

  // initialize buffer
  buffer = new info[total];

}

//default destructor
Printer::~Printer() {
    delete [] buffer;
    cout << "***********************" << endl;
}

// helper function:
void Printer::helper_print(Printer::Kind kind, char state, unsigned int lid, int value1, int value2){
	// find index
	int index = (int) kind;

	if(lid > 0)
		index += lid;

	// Check overwrite condition
    // flush buffer if it is overwritten
    if(buffer[kind].overwrite){
        Printer::flush(false);
    }

    // Add variables to the buffer for the given voter id
    buffer[kind].overwrite = true;
    buffer[kind].state = state;  
    buffer[kind].lid = lid;
    buffer[kind].value1 = value1;
    buffer[kind].value2 = value2;

    // first of all, need to check whether voting is Finished
    if(state == 'F'){
        Printer::flush(true);
    }
}


void Printer::print( Kind kind, char state ){
	helper_print(kind, state, -1, -1, -1);
}

void Printer::print( Kind kind, char state, int value1 ){
	helper_print(kind, state, -1, value1, -1);
}

void Printer::print( Kind kind, char state, int value1, int value2 ){
	helper_print(kind, state, -1, value1, value2);
}

void Printer::print( Kind kind, unsigned int lid, char state ){
	helper_print(kind, state, lid, -1, -1);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
	helper_print(kind, state, lid, value1, -1);
}	

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
	helper_print(kind, state, lid, value1, value2);
}	


// print appropriate state accordin to buffer
// and reset buffer
void Printer::flush(bool isFinished){
 	P1: {
        for (unsigned int i = 0; i < total; ++i) {
     		if(buffer[i].overwrite){
				cout << (char)buffer[i].state;

                if(buffer[i].value1 != -1){
                	cout << buffer[i].value1;
                	if(buffer[i].value2 != -1){
                		cout << ", " << buffer[i].value2;
                	}
                }
              
                //reset buffer
                buffer[i].overwrite = false;
     		}
            else if(isFinished){
                cout << "..."; 
            }
     		cout << "\t";
     	}
    }
 	cout << "\n";
 }

// End: //