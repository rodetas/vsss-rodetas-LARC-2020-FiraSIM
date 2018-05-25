//
// Created by manoel on 07/05/18.
//
#include "TransmissionTests.h"
#include <iostream>
#include <Config.h>
#include <Common.h>

using namespace std;
using namespace common;
int main(int argc, char** argv){
		TransmissionTests transmissionTests;
			
		transmissionTests.testGenerateMessage();
		transmissionTests.testCheckSum();
	return 0;
}
