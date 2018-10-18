package node.application.throughputPolicies;

// The sensor node module. Connects to the wireless channel in order to communicate 
// with other nodes. Connects to psysical processes so it can sample them.

simple ThroughputPolicies like node.application.iApplication {
 parameters:
 	string applicationID = default ("throughputTest");
	bool collectTraceInfo = default (false);
	int priority = default (0);
	int packetHeaderOverhead = default (5);		// in bytes
	int constantDataPayload = default (100);	// in bytes

	int taxa = default (80);
	double limiarBuffer = default(85.0);
	bool utilizarTaxaBuffer = default(false);

	double CCAthreshold = default (-95.0);   
	double CCAthreshold2 = default (-95.0);

	bool isSink = default(false);

	double delayLimit = default (0); 			// application delay limit (0 - no limit)
											// discard packets arriving after the limit

	string nextRecipient = default ("0");	// Destination for packets received in this node. 
											// These parameters can be used to create an
											// application-level static routing. This way we can
											// have a multi-hop throughput test   

	double packet_rate = default (0);	// packets per second, by default we transmit no packets
	double startupDelay = default (0);	// delay in seconds before the app stars producing packets

	double latencyHistogramMax = default (200);
	int latencyHistogramBuckets = default (10);

 gates:
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}
