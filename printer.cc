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
	int index;


  // cout << "TOTAL: " << total << endl;
  switch(kind){
    case Courier:
      index = total - numCouriers + lid + 1;
       // cout << "Courier : ";
      break;
    case Vending:
      index = total - numCouriers - numVendingMachines + lid ;
      // cout << "Vending : ";
      break;
    case Student:
      index = total - numCouriers - numVendingMachines - numStudents + lid;
      // cout << "Student : ";
      break;
    default:
      index = (int) kind;
      break;
  }

    // cout << index << " "  << state << " " << endl;

	// Check overwrite condition
    // flush buffer if it is overwritten
    if(buffer[index].overwrite){
        flush(false);
    }

    // Add variables to the buffer for the given kind
    buffer[index].overwrite = true;
    buffer[index].state = state;
    buffer[index].lid = lid;
    buffer[index].value1 = value1;
    buffer[index].value2 = value2;

    // first of all, need to check whether  is Finish
    if(state == 'F'){
        flush(false);
        flush(true);
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
 	cout << "\n";
 }

// End: //
