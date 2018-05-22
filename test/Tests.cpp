//
// created by Samuel on 21/05/18
//
#include <tests.h>
using namespace std; 
	string testGenerateMessage(int id, Command c){
		Transmission t;
		return t.generateMessage(id, c);
	}
	int testCheckSum(int frame, int id, int address, int option, vector<int> hex){
		Transmission t;
		return t.generateCheckSum(frame,id, address, option, hex);
	}
	