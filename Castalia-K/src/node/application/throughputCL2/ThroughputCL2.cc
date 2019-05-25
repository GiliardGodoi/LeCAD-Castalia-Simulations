#include "ThroughputCL2.h"
//#include "cstdlib"
//#include "time.h"
#include "Basic802154Control_m.h"

Define_Module(ThroughputCL2);

void ThroughputCL2::startup()
{
	taxa = par("taxa");
	isSink = par("isSink");
	CCAthreshold = par("CCAthreshold");
	CCAthreshold2 = par("CCAthreshold2");
	potencia1 = par("potencia1");
	potencia2 = par("potencia2");
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
	trace() << "Inicio"<<SELF_NETWORK_ADDRESS;
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

void ThroughputCL2::fromNetworkLayer(ApplicationPacket * rcvPacket,
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

int ThroughputCL2::getPriority(){
	int r;
//	srand(time(NULL));
	trace() << "Priority = " << priority;
	if(priority){
		r = rand()%100+1;
		trace() << "r = " << r;
		if(r>95){
			//packet_rate = 1 / float (packet_spacing*1.1);
			return 4;
		}
		else if(r>90){
			//packet_rate = 1 / float (packet_spacing);
			return 3;
		}		
		else if(r>=50){
			//packet_rate = (1 / float (packet_spacing))*1.1;
			return 2;		
		}
		else{
			//packet_rate = (1 / float (packet_spacing))*1.4;
			return 0;
		}
	}
	return -1;
}

void ThroughputCL2::timerFiredCallback(int index)
{
	int valuePriority;
	switch (index) {
		case SEND_PACKET:{
//			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,-10));
//			trace() << "Sending Mensagem PHY";
			toNetworkLayer(createGenericDataPacket(0, dataSN), recipientAddress.c_str());
//atoi(SELF_NETWORK_ADDRESS)
			valuePriority = getPriority();
			if (valuePriority>0){
				Basic802154ControlCommand *cmd = new Basic802154ControlCommand("Basic802154 control command", MAC_CONTROL_COMMAND);
				
				cmd->setBasic802154CommandKind (SET_INTERVAL);
				cmd->setParameter(valuePriority);
				trace() << "APP prioridade MAC interval = " << SET_INTERVAL << " tentativas "<<valuePriority;
				toNetworkLayer(cmd);
			}
			packetsSent[recipientId]++;
			dataSN++;
//			if (dataSN%10==0)
//				setPacketRate();
			countTransmitions();
//			trace()<<"Packet Spacing "<<packet_spacing <<" from node "<<SELF_NETWORK_ADDRESS;
			setTimer(SEND_PACKET, packet_spacing);
			break;
		}
	}
}

// This method processes a received carrier sense interupt. Used only for demo purposes
// in some simulations. Feel free to comment out the trace command.
void ThroughputCL2::handleRadioControlMessage(RadioControlMessage *radioMsg)
{
	switch (radioMsg->getRadioControlMessageKind()) {
		case CARRIER_SENSE_INTERRUPT:
//			trace() << "CS Interrupt received! current RSSI value is: " << radioModule->readRSSI();
                        break;
	}
}

void ThroughputCL2::finishSpecific() {
	declareOutput("Packets reception rate");
	declareOutput("Packets loss rate");

	trace()<<"Pacotestransmitidospor "<<SELF_NETWORK_ADDRESS<<" = "<<getPacketCount(atoi(SELF_NETWORK_ADDRESS));

	cTopology *topo;	// temp variable to access packets received by other nodes
	topo = new cTopology("topo");
	topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());

	long bytesDelivered = 0;
	for (int i = 0; i < numNodes; i++) {
		ThroughputCL2 *appModule = dynamic_cast<ThroughputCL2*>
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

int ThroughputCL2::getPacketCount(int node){
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

void ThroughputCL2::countTransmitions(){
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

int ThroughputCL2::handleControlCommand(cMessage * msg){

	double taxaMAC = 0.0;

	if(atoi(SELF_NETWORK_ADDRESS)!=0){
//		trace()<<"Packet Spacing " << packet_spacing << " Packet Rate " << packet_rate;
//		trace() << "Chegou APP ";
		CrossLayerMsg *cmd = check_and_cast <CrossLayerMsg*>(msg);
		taxaMAC = cmd->getTaxaMAC();
		trace() << "TAXA_MAC    "<<taxaMAC;

		if (taxaMAC < taxa){
			trace() << " Altera1 " << potencia1 << " TaxaMAC " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia1));
			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold2));
		} else {
			trace() << " Altera2 " << potencia2 << " TaxaMAC " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia2));
			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold));
		}


//		if (cmd->getParameter() == 1 && packet_rate <= packet_rate_safe && packet_rate > 1){
//			packet_rate = packet_rate - 1;
//		} else if (cmd->getParameter() == 2 && packet_rate <= packet_rate_safe && packet_rate >= 0){
//			packet_rate = packet_rate + 1;
//		}
//		if(packet_spacing >= 0 && packet_rate <= packet_rate_safe && packet_rate >= 0){
//			trace()<<"Entrando Packet Spacing " << packet_spacing << " Packet Rate " << packet_rate;
//			packet_spacing = 1 / float (packet_rate);
//			trace()<<"Packet Spacing " << packet_spacing << " Packet Rate " << packet_rate;
//		}else{
//			trace()<<"Saindo Packet Spacing " << packet_spacing << " Packet Rate " << packet_rate;
//			packet_rate = packet_rate_safe;
//			packet_spacing = 1 / float (packet_rate);
//		}
//		trace()<<"Packet Spacing " << packet_spacing << " Packet Rate " << packet_rate;
		delete cmd;
	}
	return 1;
}
