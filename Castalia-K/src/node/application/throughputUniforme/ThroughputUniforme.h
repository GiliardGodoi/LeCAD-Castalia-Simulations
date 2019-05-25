#ifndef _THROUGHPUTTEST_H_
#define _THROUGHPUTTEST_H_

#include "VirtualApplication.h"
#include "CrossLayerMsg_m.h"
#include <map>
#include <random>

using namespace std;

enum ThroughputUniformeTimers {
	SEND_PACKET = 1
};

class ThroughputUniforme: public VirtualApplication {
 private:
	double packet_rate;
	double startupDelay;
	double delayLimit;
	float packet_spacing;
	int dataSN;
	int recipientId;
	string recipientAddress;
	int vetorPotencia[5];
	
	int taxa;
	
	double CCAthreshold;
	double CCAthreshold2;
	bool isSink;

	//variables below are used to determine the packet delivery rates.	
	int numNodes;
	map<long,int> packetsReceived;
	map<long,int> bytesReceived;
	map<long,int> packetsSent;

	// RANDOM STUFF
	static random_device rd;
    static mt19937 gen;
    static uniform_int_distribution<> dis;
	int potenciaAtual = 0;

 protected:
	void startup();
	void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
	void handleRadioControlMessage(RadioControlMessage *);
	void timerFiredCallback(int);
	void finishSpecific();
	int getPriority();
	void varyTriesByBufferState(double);
	int handleControlCommand(cMessage * msg);

 public:
	int getPacketsSent(int addr) { return packetsSent[addr]; }
	int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	int getBytesReceived(int addr) { return bytesReceived[addr]; }
	
};

#endif				// _THROUGHPUTTEST_APPLICATIONMODULE_H_
