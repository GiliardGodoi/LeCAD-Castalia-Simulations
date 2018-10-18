#include "ThroughputPolicies.h"
//#include "cstdlib"
//#include "time.h"
#include "Basic802154Control_m.h"

Define_Module(ThroughputPolicies);

random_device ThroughputPolicies::rd;
mt19937 ThroughputPolicies::gen(ThroughputPolicies::rd());
//uniform_int_distribution<> ThroughputPolicies::dis(0,4);
binomial_distribution<> ThroughputPolicies::dis(4, 0.7);

void ThroughputPolicies::startup()
{
	vetorPotencia[0] = -25;
	vetorPotencia[1] = -20;
	vetorPotencia[2] = -15;
	vetorPotencia[3] = -12;
	vetorPotencia[4] = -10;

	taxa = par("taxa");
	isSink = par("isSink");

	CCAthreshold = par("CCAthreshold");
	CCAthreshold2 = par("CCAthreshold2");

	priority = par("priority");
	packet_rate = par("packet_rate");
	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1;
	
	recipientAddress = par("nextRecipient").stringValue();
	recipientId = atoi(recipientAddress.c_str());
	startupDelay = par("startupDelay");
	delayLimit = par("delayLimit");
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

void ThroughputPolicies::fromNetworkLayer(ApplicationPacket * rcvPacket,
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

int ThroughputPolicies::getPriority(){
	int r;
//	trace() << "Priority = " << priority;
	if(priority){
		r = rand()%100+1;
//		trace() << "VALORDER = " << r;
		if(r>40){
//			trace() << "PRIORIDADE4"; 
			return 4;
		}
		else if(r>30){
//			trace() << "PRIORIDADE3";
			return 3;
		}		
		else if(r>=20){
//			trace() << "PRIORIDADE2"; 
			return 2;		
		}
		else{
//			trace() << "PRIORIDADE0"; 
			return 0;
		}
	}
//	trace() << "PRIORIDADENULA"; 
	return -1;
}

void ThroughputPolicies::timerFiredCallback(int index)
{
	int valuePriority;
	switch (index) {
		case SEND_PACKET:{
			toNetworkLayer(createGenericDataPacket(0, dataSN), recipientAddress.c_str());
			valuePriority = getPriority();
			if (valuePriority > 0){
				Basic802154ControlCommand *cmd = new Basic802154ControlCommand("Basic802154 control command", MAC_CONTROL_COMMAND);
				
				cmd->setBasic802154CommandKind (SET_INTERVAL); // envio para camada MAC
				cmd->setParameter(valuePriority);
				trace() << "APP prioridade MAC interval = " << SET_INTERVAL << " tentativas "<<valuePriority;
				toNetworkLayer(cmd);
			}

			packetsSent[recipientId]++;
			dataSN++;
			setTimer(SEND_PACKET, packet_spacing);
			break;
		}
	}
}

// This method processes a received carrier sense interupt. Used only for demo purposes
// in some simulations. Feel free to comment out the trace command.
void ThroughputPolicies::handleRadioControlMessage(RadioControlMessage *radioMsg)
{
	switch (radioMsg->getRadioControlMessageKind()) {
		case CARRIER_SENSE_INTERRUPT:
//			trace() << "CS Interrupt received! current RSSI value is: " << radioModule->readRSSI();
                        break;
	}
}

void ThroughputPolicies::finishSpecific() {
	declareOutput("Packets sent");
	declareOutput("Packets reception rate");
	declareOutput("Packets loss rate");

	cTopology *topo;	// temp variable to access packets received by other nodes
	topo = new cTopology("topo");
	topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());

	long bytesDelivered = 0;
	for (int i = 0; i < numNodes; i++) {
		ThroughputPolicies *appModule = dynamic_cast<ThroughputPolicies*>
			(topo->getNode(i)->getModule()->getSubmodule("Application"));
		if (appModule) {
			int packetsSent = appModule->getPacketsSent(self);			
			if (packetsSent > 0) { // this node sent us some packets
				float rate = (float)packetsReceived[i]/packetsSent;
				trace()<<"Pacotesrecebidos " <<i<<" "<<packetsReceived[i]<< " Pacotestransmitidos "<<packetsSent<<" Rate "<<rate;
				collectOutput("Packets sent",i,"total",packetsSent);
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

void ThroughputPolicies::varyTriesByBufferState(double state)
{	
	Basic802154ControlCommand *cmdPrioridade = new Basic802154ControlCommand("Basic802154 control command", MAC_CONTROL_COMMAND);
	cmdPrioridade->setBasic802154CommandKind(SET_INTERVAL); // envio para camada

	if(state > limiarBuffer)
	{
		cmdPrioridade->setParameter(1);
	}
	else
	{
		cmdPrioridade->setParameter(2);
	}
	
	toNetworkLayer(cmdPrioridade);
}

int ThroughputPolicies::handleControlCommand(cMessage * msg){

	
	int nroRandomico = dis(gen);
	int potencia = vetorPotencia[nroRandomico];
	
	
	trace() << "RANDOMICO    " << nroRandomico << "    POTENCIA    " << potencia;

	ThroghputPriorityMsg *cmd = check_and_cast <ThroghputPriorityMsg*>(msg);
	int INFO_TYPE = cmd->getType();

	switch (INFO_TYPE) {
		
		case TAXAMAC_INFO : {
			trace() << "TAXAMAC_INFO    " << cmd->getTaxaMAC() << "    BUFFER_INFO    " << cmd->getBufferState();
			break;	
		}
		case BUFFER_INFO : {
			double state = cmd->getBufferState();
			if(utilizarTaxaBuffer)
			{
				varyTriesByBufferState(state);
			}
			trace() << "BUFFER_INFO    " << state << "    POTENCIA    " << potenciaAtual << "    IS_TAXA_BUFFER    " << utilizarTaxaBuffer;
			
		}
	}

	potenciaAtual = potencia;
	toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));

	delete cmd;
	return 2;
}
