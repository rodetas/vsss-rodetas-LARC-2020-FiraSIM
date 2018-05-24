// 
// Created by Samuel on 21/05/18
//

#include <Transmission.h>
#include <cstring>
#include <Common.h>
#include <assert.h>
using namespace std;
using namespace common;
class TransmissionTests{
	public:
	void testGenerateMessage(){
		Transmission t;
		int id=0;
		Command c;
		c.left=255;
		c.right=255;
		assert(t.generateMessage(id, c)=="7e000c0101000000463235353235357f");
		id=1;
		c.left=123;
		c.right=123;
		assert(t.generateMessage(id, c)== "7e000c0101000100423132333132338e");
	}
	void testCheckSum(){
		int	id=0x01, frame=0x01, address=0, option=0;
		vector<int> hex={0x42, 0x31, 0x32, 0x33, 0x31, 0x32, 0x33};	
		Transmission t;
		assert(t.generateCheckSum(frame,id, address, option, hex)==0x8f);
		hex={0x4C, 0x32, 0x35, 0x35, 0x32, 0x35, 0x35};
		assert(t.generateCheckSum(frame, id, address, option, hex)==0x79);
		
	}	
};
