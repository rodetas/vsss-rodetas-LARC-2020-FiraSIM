// 
// Created by Samuel on 21/05/18
//

#include <Transmission.h>
#include <Common.h>
#include <assert.h>

using namespace std;
using namespace common;

class TransmissionTests{

public:

    Transmission t;

	void testGenerateMessage(){
		int id=0;
		Command c(255,255);

		assert(t.generateMessage(id, c) == "7e000c0101000000323535323535c5");

		id=1;
		c = Command(123,123);

		assert(t.generateMessage(id, c)== "7e000c0101000100313233313233d0");
	}

	void testCheckSum(){
		int	id=0x01, frame=0x01, address=0, option=0;

		vector<int> hex={0x42, 0x31, 0x32, 0x33, 0x31, 0x32, 0x33};

		assert(t.generateCheckSum(frame,id, address, option, hex)==0x8f);

		hex={0x4C, 0x32, 0x35, 0x35, 0x32, 0x35, 0x35};

		assert(t.generateCheckSum(frame, id, address, option, hex)==0x79);
	}

};
