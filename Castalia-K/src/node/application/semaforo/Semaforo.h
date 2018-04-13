#ifndef _SEMAFORO_H_
#define _SEMAFORO_H_

#include "VirtualApplication.h"
#include <map>

using namespace std;

enum SemaforoTestTimers {
	SEND_PACKET = 1
};

class Semaforo: public VirtualApplication {
 private:
	double packet_rate;
	double startupDelay;
	double delayLimit;
	float packet_spacing;
	int dataSN;
	int recipientId;
	string recipientAddress;
	
	//variables below are used to determine the packet delivery rates.	
	int numNodes;
	map<long,int> packetsReceived;
	map<long,int> bytesReceived;
	map<long,int> packetsSent;

 protected:
	void startup();
	void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
	void handleRadioControlMessage(RadioControlMessage *);
	void timerFiredCallback(int);
	void finishSpecific();

 public:
	int getPacketsSent(int addr) { return packetsSent[addr]; }
	int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	int getBytesReceived(int addr) { return bytesReceived[addr]; }
	
};

#endif				// _THROUGHPUTTEST_APPLICATIONMODULE_H_
