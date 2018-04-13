#include "SensoringTest.h"

Define_Module(SensoringTest);

void SensoringTest::startup()
{
	packet_rate = par("packet_rate");
	recipientAddress = par("nextRecipient").stringValue();
	recipientId = atoi(recipientAddress.c_str());
	startupDelay = par("startupDelay");
	delayLimit = par("delayLimit");
	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1;
	dataSN = 0;
	
	numNodes = getParentModule()->getParentModule()->par("numNodes");
	packetsSent.clear();
	packetsReceived.clear();
	bytesReceived.clear();

	if (packet_spacing > 0 && recipientAddress.compare(SELF_NETWORK_ADDRESS) != 0)
		setTimer(SEND_PACKET, packet_spacing + startupDelay);
	else
		trace() << "Not sending packets";

	declareOutput("Packets received per node");
}

void SensoringTest::fromNetworkLayer(ApplicationPacket * rcvPacket,
		const char *source, double rssi, double lqi)
{
	int sequenceNumber = rcvPacket->getSequenceNumber();
	int sourceId = atoi(source);

	// This node is the final recipient for the packet
	if (recipientAddress.compare(SELF_NETWORK_ADDRESS) == 0) {
		if (delayLimit == 0 || (simTime() - rcvPacket->getCreationTime()) <= delayLimit) { 
			trace() << "Received packet #" << sequenceNumber << " from node " << source;
			trace() << "RSSI " << rssi;
			collectOutput("Packets received per node", sourceId);
			packetsReceived[sourceId]++;
			bytesReceived[sourceId] += rcvPacket->getByteLength();
		} else {
			trace() << "Packet #" << sequenceNumber << " from node " << source <<
				" exceeded delay limit of " << delayLimit << "s";
		}
	// Packet has to be forwarded to the next hop recipient
	} else {
		ApplicationPacket* fwdPacket = rcvPacket->dup();
		// Reset the size of the packet, otherwise the app overhead will keep adding on
		fwdPacket->setByteLength(0);
		toNetworkLayer(fwdPacket, recipientAddress.c_str());
	}
}

void SensoringTest::timerFiredCallback(int index)
{
	switch (index) {
		case SEND_PACKET:{
			setTimer(SEND_PACKET, packet_spacing);
			requestSensorReading();
			break;
		}
	}
}

// This method processes a received carrier sense interupt. Used only for demo purposes
// in some simulations. Feel free to comment out the trace command.
void SensoringTest::handleRadioControlMessage(RadioControlMessage *radioMsg)
{
	switch (radioMsg->getRadioControlMessageKind()) {
		case CARRIER_SENSE_INTERRUPT:
			trace() << "CS Interrupt received! current RSSI value is: " << radioModule->readRSSI();
                        break;
	}
}

void SensoringTest::handleSensorReading(SensorReadingMessage * sensorMsg)
{
	string sensType(sensorMsg->getSensorType());
	double sensValue = sensorMsg->getSensedValue();
	Sensoring* fwdPacket = new Sensoring(sensType.c_str(),APPLICATION_PACKET);
	Info data;
	data.nodeID = (unsigned short)self;
	data.locX = mobilityModule->getLocation().x;
	data.locY = mobilityModule->getLocation().y;
	data.sensData = sensValue*((sensType.compare("Temperature")==0)?80:1);
	data.payload = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	fwdPacket -> setExtraData(data);
	trace() << "Sending packet #" << dataSN;
	trace() << "X = " << fwdPacket->getExtraData().locX << "\tY = " << fwdPacket->getExtraData().locY << "\t" << sensType << " = " << fwdPacket->getExtraData().sensData;
	toNetworkLayer(fwdPacket, recipientAddress.c_str());
	packetsSent[recipientId]++;
	dataSN++;
}

void SensoringTest::finishSpecific() {
	declareOutput("Packets reception rate");
	declareOutput("Packets loss rate");

	cTopology *topo;	// temp variable to access packets received by other nodes
	topo = new cTopology("topo");
	topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());

	long bytesDelivered = 0;
	for (int i = 0; i < numNodes; i++) {
		SensoringTest *appModule = dynamic_cast<SensoringTest*>
			(topo->getNode(i)->getModule()->getSubmodule("Application"));
		if (appModule) {
			int packetsSent = appModule->getPacketsSent(self);
			if (packetsSent > 0) { // this node sent us some packets
				float rate = (float)packetsReceived[i]/packetsSent;
				collectOutput("Packets reception rate", i, "total", rate);
				collectOutput("Packets loss rate", i, "total", 1-rate);
			}

			bytesDelivered += appModule->getBytesReceived(self);
		}
	}
	delete(topo);

	if (packet_rate > 0 && bytesDelivered > 0) {
		double energy = (resMgrModule->getSpentEnergy() * 1000000000)/(bytesDelivered * 8);	//in nanojoules/bit
		declareOutput("Energy nJ/bit");
		collectOutput("Energy nJ/bit","",energy);
	}
}
