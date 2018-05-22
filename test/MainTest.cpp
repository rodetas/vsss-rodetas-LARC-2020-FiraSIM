//
// Created by manoel on 07/05/18.
//
#include "tests.h"
#include <iostream>
#include <Config.h>
#include <Common.h>

using namespace std;
using namespace common;
int main(int argc, char** argv){
	if(Config::argumentParse(argc, argv)){
		tests tests;
		int	id, frame, address, option;
		vector<int> hex={0x42, 0x31, 0x32, 0x33, 0x31, 0x32, 0x33};
		Command c;
		//if(Config::test="t1"){
			cin >> id;
			cin >> c.left;
			cin >> c.right;
			cout << tests.testGenerateMessage( id, c) << endl;
		//}
			//colocar if separando os casos
		//else if(Config::test="t2){ 
				cin >> frame;
				cin >> id;
				cin >> address; 
				cin >> option;
				cout << tests.testCheckSum(frame, id, address, option, hex) << endl;
				//}
			//else cout << "Invalid Test" << endl;
	}
	return 0;
}
