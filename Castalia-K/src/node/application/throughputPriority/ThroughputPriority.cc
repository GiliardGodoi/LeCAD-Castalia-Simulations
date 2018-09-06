#include "ThroughputPriority.h"
#include "Basic802154Control_m.h"
Define_Module(ThroughputPriority);

void ThroughputPriority::startup()
{
	taxa = par("taxa");
	isSink = par("isSink");

	CCAthreshold = par("CCAthreshold");
	CCAthreshold2 = par("CCAthreshold2");

	priority = par("priority");

	packet_rate = par("packet_rate");
	packet_rate_safe = par("packet_rate");
	recipientAddress = par("nextRecipient").stringValue();
	recipientId = atoi(recipientAddress.c_str());
	startupDelay = par("startupDelay");
	delayLimit = par("delayLimit");
	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1;
	packet_spacing_safe = packet_spacing;
//	packet_spacing = packet_rate;
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

void ThroughputPriority::fromNetworkLayer(ApplicationPacket * rcvPacket,
		const char *source, double rssi, double lqi)
{
	int sequenceNumber = rcvPacket->getSequenceNumber();
	int sourceId = atoi(source);
	// This node is the final recipient for the packet
	if (recipientAddress.compare(SELF_NETWORK_ADDRESS) == 0) {
		if (delayLimit == 0 || (simTime() - rcvPacket->getCreationTime()) <= delayLimit) {
//			trace() << "Received packet #" << sequenceNumber << " from node " << source;
			collectOutput("Packets received per node", sourceId);
			packetsReceived[sourceId]++;
			bytesReceived[sourceId] += rcvPacket->getByteLength();
		} else {
//			trace() << "Packet #" << sequenceNumber << " from node " << source <<
//				" exceeded delay limit of " << delayLimit << "s";
		}
	// Packet has to be forwarded to the next hop recipient
	} else {
		ApplicationPacket* fwdPacket = rcvPacket->dup();
		// Reset the size of the packet, otherwise the app overhead will keep adding on
		fwdPacket->setByteLength(0);
//		toNetworkLayer(fwdPacket, recipientAddress.c_str());
		toNetworkLayer(fwdPacket, recipientAddress.c_str());
	}
}

int ThroughputPriority::getPriority(){
	return 2;
}

void ThroughputPriority::timerFiredCallback(int index)
{
	int valuePriority;
	switch (index) {
		case SEND_PACKET:{
	
			toNetworkLayer(createGenericDataPacket(0, dataSN), recipientAddress.c_str());
//atoi(SELF_NETWORK_ADDRESS)
			valuePriority = getPriority();
			if (valuePriority>0){
				Basic802154ControlCommand *cmd = new Basic802154ControlCommand("Basic802154 control command", MAC_CONTROL_COMMAND);
				
				cmd->setBasic802154CommandKind (SET_INTERVAL); // envio para camada MAC
				cmd->setParameter(valuePriority);
//				trace() << "APP prioridade MAC interval = " << SET_INTERVAL << " tentativas "<<valuePriority;
				toNetworkLayer(cmd);
			}
			packetsSent[recipientId]++;
			dataSN++;
//			if (dataSN%10==0)
//				setPacketRate();
//			countTransmitions();
//			trace()<<"Packet Spacing "<<packet_spacing <<" from node "<<SELF_NETWORK_ADDRESS;
			setTimer(SEND_PACKET, packet_spacing);
			break;
		}
	}
}

// This method processes a received carrier sense interupt. Used only for demo purposes
// in some simulations. Feel free to comment out the trace command.
void ThroughputPriority::handleRadioControlMessage(RadioControlMessage *radioMsg)
{
	switch (radioMsg->getRadioControlMessageKind()) {
		case CARRIER_SENSE_INTERRUPT:
//			trace() << "CS Interrupt received! current RSSI value is: " << radioModule->readRSSI();
                        break;
	}
}

void ThroughputPriority::finishSpecific() {
	declareOutput("Packets reception rate");
	declareOutput("Packets loss rate");

	trace()<<"Pacotestransmitidospor "<<SELF_NETWORK_ADDRESS<<" = "<<getPacketCount(atoi(SELF_NETWORK_ADDRESS));

	cTopology *topo;	// temp variable to access packets received by other nodes
	topo = new cTopology("topo");
	topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());

	long bytesDelivered = 0;
	for (int i = 0; i < numNodes; i++) {
		ThroughputPriority *appModule = dynamic_cast<ThroughputPriority*>
			(topo->getNode(i)->getModule()->getSubmodule("Application"));
		if (appModule) {
			int packetsSent = appModule->getPacketsSent(self);			
			if (packetsSent > 0) { // this node sent us some packets
				float rate = (float)packetsReceived[i]/packetsSent;
				trace()<<"Pacotesrecebidos " <<i<<" "<<packetsReceived[i]<< " Pacotestransmitidos "<<packetsSent<<" Rate "<<rate;
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
		trace()<<"SpentEnergy "<<resMgrModule->getSpentEnergy()<<" EnergynJ/bit "<<energy;
	}
}

int ThroughputPriority::getPacketCount(int node){
	switch (node) {
			case 1:{
				nTime1++;
				return nPacket1/nTime1;
				break;
			}

			case 2:{
				nTime2++;
				return nPacket2/nTime2;
				break;
			}
			case 3:{
				nTime3++;
				return nPacket3/nTime3;
				break;
			}
			case 4:{
				nTime4++;
				return nPacket4/nTime4;
				break;
			}
			case 5:{
				nTime5++;
				return nPacket5/nTime5;
				break;
			}
			case 0:{
				return nPacket0;
				break;
			}
		}
}

void ThroughputPriority::countTransmitions(){
	switch (atoi(SELF_NETWORK_ADDRESS)) {
			case 1:{
				nPacket1++;
				break;
			}

			case 2:{
				nPacket2++;
				break;
			}
			case 3:{
				nPacket3++;
				break;
			}
			case 4:{
				nPacket4++;
				break;
			}
			case 5:{
				nPacket5++;
				break;
			}
			case 0:{
				nPacket0++;
				break;
			}
		}
}

int ThroughputPriority::handleControlCommand(cMessage * msg){

	 return 2;
}
