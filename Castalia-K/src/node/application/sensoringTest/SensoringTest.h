#ifndef _SENSORINGTEST_H_
#define _SENSORINGTEST_H_

#include "VirtualApplication.h"
#include "Sensoring_m.h"
#include <map>

using namespace std;

enum SensoringTestTimers {
	SEND_PACKET = 1
};

class SensoringTest: public VirtualApplication {
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
	void handleSensorReading(SensorReadingMessage * sensorMsg);
	void timerFiredCallback(int);
	void finishSpecific();

 public:
	int getPacketsSent(int addr) { return packetsSent[addr]; }
	int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	int getBytesReceived(int addr) { return bytesReceived[addr]; }
	
};

#endif				// _SENSORINGTEST_APPLICATIONMODULE_H_
