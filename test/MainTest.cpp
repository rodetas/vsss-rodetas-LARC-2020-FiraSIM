//
// Created by manoel on 07/05/18.
//

#include "TransmissionTests.h"

int main(int argc, char** argv){
    TransmissionTests transmissionTests;

    transmissionTests.testGenerateMessage();
    transmissionTests.testCheckSum();
    
	return 0;
}
