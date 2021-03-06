#ifndef _THROUGHPUTTEST_H_
#define _THROUGHPUTTEST_H_

#include "VirtualApplication.h"
#include "CrossLayerMsg_m.h"
#include <map>

using namespace std;

enum ThroughputCL4Timers {
	SEND_PACKET = 1
};

class ThroughputCL4: public VirtualApplication {
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

    // Variables used to count transmission at application layer
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
    float packet_spacing_safe;
    
    int priority;

    int potenciaFinal = 0;
    double taxaMAC = 0.0;

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
