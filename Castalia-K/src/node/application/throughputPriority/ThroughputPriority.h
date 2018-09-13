#ifndef _THROUGHPUTTEST_H_
#define _THROUGHPUTTEST_H_

#include "VirtualApplication.h"
#include "ThroughputTestControl_m.h"
#include "ThroughputPriorityMsg_m.h"
#include <map>

using namespace std;

enum ThroughputPriorityTimers {
	SEND_PACKET = 1
};

class ThroughputPriority: public VirtualApplication {
 private:
	double packet_rate;
	double startupDelay;
	double delayLimit;
	float packet_spacing;
	int dataSN;
	int recipientId;
	string recipientAddress;

	int nPacket1 = 0;
	int nPacket2 = 0;
	int nPacket3 = 0;
	int nPacket4 = 0;
	int nPacket5 = 0;
	int nPacket0 = 0;

	int nTime1 = 0;
	int nTime2 = 0;
	int nTime3 = 0;
	int nTime4 = 0;
	int nTime5 = 0;
	
	int packet_rate_safe;
	int priority;
	
	int potencia = 0;
	int potenciaAtual = 0;

	float packet_spacing_safe;
	double taxaMAC = 0.0;
	

	bool isSink;

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
	int getPriority();
	int handleControlCommand(cMessage * msg);
	void countTransmitions();
	int getPacketCount(int node);

 public:
	int getPacketsSent(int addr) { return packetsSent[addr]; }
	int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	int getBytesReceived(int addr) { return bytesReceived[addr]; }
	
};

#endif				// _THROUGHPUTTEST_APPLICATIONMODULE_H_
