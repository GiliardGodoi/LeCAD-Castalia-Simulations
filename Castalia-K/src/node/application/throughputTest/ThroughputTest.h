#ifndef _THROUGHPUTTEST_H_
#define _THROUGHPUTTEST_H_

#include "VirtualApplication.h"
#include "ThroughputTestControl_m.h"
#include <map>

using namespace std;

enum ThroughputTestTimers {
	SEND_PACKET = 1
};

class ThroughputTest: public VirtualApplication {
 private:
	double packet_rate;
	double startupDelay;
	double delayLimit;
	float packet_spacing;
	int dataSN;
	int recipientId;
	string recipientAddress;
	
	int taxa;
	
	double CCAthreshold;
	double CCAthreshold2;

	int potencia1;
	int potencia2;
	int potencia3;
	int potencia4;
	int potencia5;
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
	int varayPowerLevel(int noIndex, int nivelAnterior, int variacao);

 public:
	int getPacketsSent(int addr) { return packetsSent[addr]; }
	int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	int getBytesReceived(int addr) { return bytesReceived[addr]; }
	
};

#endif				// _THROUGHPUTTEST_APPLICATIONMODULE_H_
