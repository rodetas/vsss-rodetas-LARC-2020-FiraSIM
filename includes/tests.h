// 
// Created by Samuel on 21/05/18
//

#include <Transmission.h>
#include <cstring>
#include <Common.h>
using namespace std;
using namespace common;
class tests{
	public:
	static string testGenerateMessage(int id, Command c);
	static int testCheckSum(int frame, int id, int address, int option, vector<int> hex);
};