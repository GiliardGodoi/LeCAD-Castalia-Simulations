#include "ThroughputTest.h"
//#include "cstdlib"
//#include "time.h"
#include "Basic802154Control_m.h"

Define_Module(ThroughputTest);

int nPacket1 = 0, nPacket2 = 0, nPacket3 = 0, nPacket4 = 0, nPacket5 = 0, nPacket0 = 0,
nTime1 = 0, nTime2 = 0, nTime3 = 0, nTime4 = 0, nTime5 = 0, packet_rate_safe, priority, potenciaFinal = 0;
float packet_spacing_safe;
double taxaMAC = 0.0;

int vetorNivelNo[] = {-1, 2, 2, 2, 2, 2};
int vetorPotencia[5];

int ThroughputTest::varayPowerLevel(int noIndex, int nivelAnterior, int variacao)
{
	int nivelAtual = nivelAnterior + variacao;
	int potencia = vetorPotencia[nivelAnterior];
	if( (nivelAtual >=0) && (nivelAtual < 4)){
		vetorNivelNo[noIndex] = nivelAtual;
		potencia = vetorPotencia[nivelAtual];
	}
	trace() << "INDEX  " << noIndex << "  ANTERIOR  " << nivelAnterior << "  VARIACAO  " << variacao;
	return potencia;
}

void ThroughputTest::startup()
{

	taxa = par("taxa");
	isSink = par("isSink");

	CCAthreshold = par("CCAthreshold");
	CCAthreshold2 = par("CCAthreshold2");

	vetorPotencia[0] = par("potencia1");//-10dBm
	vetorPotencia[1] = par("potencia2");//-12dBm
	vetorPotencia[2] = par("potencia3");//-15dBm
	vetorPotencia[3] = par("potencia4");//-20dBm
	vetorPotencia[4] = par("potencia5");//-25dBm
	
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

void ThroughputTest::fromNetworkLayer(ApplicationPacket * rcvPacket,
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

int ThroughputTest::getPriority(){
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

void ThroughputTest::timerFiredCallback(int index)
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
void ThroughputTest::handleRadioControlMessage(RadioControlMessage *radioMsg)
{
	switch (radioMsg->getRadioControlMessageKind()) {
		case CARRIER_SENSE_INTERRUPT:
//			trace() << "CS Interrupt received! current RSSI value is: " << radioModule->readRSSI();
                        break;
	}
}

void ThroughputTest::finishSpecific() {
	declareOutput("Packets reception rate");
	declareOutput("Packets loss rate");

	trace()<<"Pacotestransmitidospor "<<SELF_NETWORK_ADDRESS<<" = "<<getPacketCount(atoi(SELF_NETWORK_ADDRESS));

	cTopology *topo;	// temp variable to access packets received by other nodes
	topo = new cTopology("topo");
	topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());

	long bytesDelivered = 0;
	for (int i = 0; i < numNodes; i++) {
		ThroughputTest *appModule = dynamic_cast<ThroughputTest*>
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

int ThroughputTest::getPacketCount(int node){
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

void ThroughputTest::countTransmitions(){
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

int ThroughputTest::handleControlCommand(cMessage * msg){

	double taxaMAC = 0.0;
	// double taxa = 0.0; // teste de taxa
	int indexNO = atoi(SELF_NETWORK_ADDRESS);
	int variacao = 0; // por padrao a potencia nao deve variar

//	if(atoi(SELF_NETWORK_ADDRESS)!=0){
	if((indexNO) >= 1 && (indexNO <= 5)){ // garantir que o index no esteja dentro deste range
//		trace()<<"Packet Spacing " << packet_spacing << " Packet Rate " << packet_rate;
//		trace() << "Chegou APP ";
		ThroughputTestControlCommand *cmd = check_and_cast <ThroughputTestControlCommand*>(msg);
		taxaMAC = cmd->getParameter();
//		trace() << "TAXAMAC"<<taxaMAC;
//		trace() << "packet_rate" << packet_rate;
		int nivelAnterior = vetorNivelNo[indexNO];
		int nivelClassificado = nivelAnterior;
// ================= CONFIGURAÇÃO PARA PACKET_RATE 10 =================================

	if (taxaMAC <= 40 && ( packet_rate ==10  ) ) { 
//			trace() << " ALTERADO PARA POTENCIA1 " << potencia1;
//			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia1)); 
//			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold2));
			nivelClassificado = 0;
			variacao = -1; // aqui o nivel incrementa de qualquer jeito
			// funcao que varia a potencia ... varayPowerLevel(int noIndex, int nivelAnterior, int variacao)
			int potencia = varayPowerLevel(indexNO,nivelAnterior, variacao);
			trace() << "NO  " << indexNO << "  ALTERADO PARA POTENCIA  " << potencia << "  TAXA MAC  " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
		} 

		else if (taxaMAC < 70 && ( packet_rate == 10 ) ) {
//			trace() << " ALTERADO PARA POTENCIA2" << potencia2;
//			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia2));
//			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold));
			nivelClassificado = 1;
			if (nivelClassificado < nivelAnterior) {
				variacao = -1;
			} 
			else if ( nivelClassificado > nivelAnterior) {
				variacao = +1;
			}
			else {
				variacao = 0;
			}
			int potencia = varayPowerLevel(indexNO,nivelAnterior, variacao);
			trace() << "NO  " << indexNO << "  ALTERADO PARA POTENCIA  " << potencia << "  TAXA MAC  " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
		}

		else if (taxaMAC < 90 && ( packet_rate == 10) ) {
//			trace() << " ALTERADO PARA POTENCIA3" << potencia3;
//			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia3));
//			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold));
			nivelClassificado = 2;
			if (nivelClassificado < nivelAnterior) {
				variacao = -1;
			} 
			else if ( nivelClassificado > nivelAnterior) {
				variacao = +1;
			}
			else {
				variacao = 0;
			}
			int potencia = varayPowerLevel(indexNO,nivelAnterior, variacao);
			trace() << "NO  " << indexNO << "  ALTERADO PARA POTENCIA  " << potencia << "  TAXA MAC  " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
		}

		else if (taxaMAC >= 90 && (packet_rate == 10) ){
//			trace() << " ALTERADO PARA POTENCIA4" << potencia4;
//			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia4));
//			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold));
			nivelClassificado = 3;
			if (nivelClassificado < nivelAnterior) {
				variacao = -1;
			} 
			else if ( nivelClassificado > nivelAnterior) {
				variacao = +1;
			}
			else {
				variacao = 0;
			}
			int potencia = varayPowerLevel(indexNO,nivelAnterior, variacao);
			trace() << "NO  " << indexNO << "  ALTERADO PARA POTENCIA  " << potencia << "  TAXA MAC  " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
		}
// =================== CONFIGURAÇÃO PARA PACKET_RATE 15 ===============================

		else if ( taxaMAC <= 40 &&  (packet_rate ==15) ) { 
//			trace() << " ALTERADO PARA POTENCIA1 " << potencia1;
//			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia1)); 
//			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold2));
			nivelClassificado = 0;
			variacao = -1;
			int potencia = varayPowerLevel(indexNO,nivelAnterior, variacao);
			trace() << "NO  " << indexNO << "  ALTERADO PARA POTENCIA  " << potencia << "  TAXA MAC  " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
		} 

		else if (taxaMAC < 70 && (packet_rate ==15)  ) {
//			trace() << " ALTERADO PARA POTENCIA2" << potencia2;
//			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia2));
//			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold));
			nivelClassificado = 1;
			if (nivelClassificado < nivelAnterior) {
				variacao = +1;
			} 
			else if ( nivelClassificado > nivelAnterior) {
				variacao = -1;
			}
			else {
				variacao = 0;
			}
			int potencia = varayPowerLevel(indexNO,nivelAnterior, variacao);
			trace() << "NO  " << indexNO << "  ALTERADO PARA POTENCIA  " << potencia << "  TAXA MAC  " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
		}

		else if (taxaMAC < 90 && (packet_rate ==15)  ) {
//			trace() << " ALTERADO PARA POTENCIA3" << potencia3;
//			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia3));
//			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold));
			nivelClassificado = 2;
			if (nivelClassificado < nivelAnterior) {
				variacao = -1;
			} 
			else if ( nivelClassificado > nivelAnterior) {
				variacao = +1;
			}
			else {
				variacao = 0;
			}
			int potencia = varayPowerLevel(indexNO,nivelAnterior, variacao);
			trace() << "NO  " << indexNO << "  ALTERADO PARA POTENCIA  " << potencia << "  TAXA MAC  " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
		}

		else if (taxaMAC >= 90 && (packet_rate ==15)  ) {
//			trace() << " ALTERADO PARA POTENCIA4" << potencia4;
//			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia4));
//			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold));
			nivelClassificado = 3;
			if (nivelClassificado < nivelAnterior) {
				variacao = -1;
			} 
			else if ( nivelClassificado > nivelAnterior) {
				variacao = +1;
			}
			else {
				variacao = 0;
			}
			int potencia = varayPowerLevel(indexNO,nivelAnterior, variacao);
			trace() << "NO  " << indexNO << "  ALTERADO PARA POTENCIA  " << potencia << "  TAXA MAC  " << taxaMAC;
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
		}


//====================== CONFIGURAÇÃO PARA PARA PACKET_RATE 25 =======================

		else if (taxaMAC <= 100 && (packet_rate ==25) ) { 
//			trace() << " ALTERADO PARA POTENCIA4 " << potencia1;
			int potencia = vetorPotencia[0];
			toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
			trace() << "NO  " << indexNO << "  ALTERADO PARA POTENCIA  " << potencia << "  TAXA MAC  " << taxaMAC;
//			toNetworkLayer(createRadioCommand(SET_CCA_THRESHOLD,CCAthreshold2)); 
		} 

//====================================================================================		
	
//		if (cmd->getParameter() == 1 && packet_rate <= packet_rate_safe && packet_rate > 1){
//			packet_rate = packet_rate - 1;
//		} else if (cmd->getParameter() == 2 && packet_rate <= packet_rate_safe && packet_rate >= 0){
//			packet_rate = packet_rate + 1;
//		}
//		
		delete cmd;
	} 

	 return 1;
}
