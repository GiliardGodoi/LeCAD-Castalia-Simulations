
package node.communication.mac.mac802154;

simple Basic802154 like node.communication.mac.iMac {
 parameters:
    //debug parameters
	bool collectTraceInfo = default (false);
	bool printStateTransitions = default (false);

	//mac layer parameters
	int macMaxPacketSize = default (142);	//128 (Maximum payload for 802.15.4) + 14 (Data packet overhead)
	int macPacketOverhead = default (14);
	int macBufferSize = default (32);

	bool enableSlottedCSMA = default (true);
	bool isFFD = default (false);
	bool isPANCoordinator = default (false);
	bool batteryLifeExtention = default (false);

	int frameOrder = default (4);
	int beaconOrder = default (6);
	int unitBackoffPeriod = default (20);
	int baseSlotDuration = default (60);

	int numSuperframeSlots = default (16);
	int macMinBE = default (5);
	int macMaxBE = default (7);
	int macMaxCSMABackoffs = default (4);
	int macMaxFrameRetries = default (2);
	int maxLostBeacons = default (4);
	int minCAPLength = default (440);

	// parameters dependent on physical layer
	// some are essential and are not defined as default
	double phyDelayForValidCS = default (0.128);
	double phyDataRate;
	double phyDelaySleep2Tx = default (0.2); //in ms
	double phyDelayRx2Tx = default (0.02);	//in ms
	int phyFrameOverhead = default (6);
	int phyBitsPerSymbol; 

	//reception guard time, in ms
	double guardTime = default (1);

	int janela = default(5);
	int ackCount = default(0);
	int packtCount  = default(0);
	int sequenceRecordTaxaMAC = default(0);

	int totalPackets  = default(0);
	int totalAcks = default(0);

 gates:
	output toNetworkModule;
	output toRadioModule;
	input fromNetworkModule;
	input fromRadioModule;
	input fromCommModuleResourceMgr;
}

