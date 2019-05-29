#include "ThroughputPolicies.h"
//#include "cstdlib"
//#include "time.h"
#include "Basic802154Control_m.h"
Define_Module(ThroughputPolicies);

int nPacket1 = 0,
	nPacket2 = 0,
	nPacket3 = 0,
	nPacket4 = 0,
	nPacket5 = 0,
	nPacket0 = 0;

int nTime1 = 0,
	nTime2 = 0,
	nTime3 = 0,
	nTime4 = 0,
	nTime5 = 0,
	packet_rate_safe,
	priority,
	potenciaFinal = 0;

float packet_spacing_safe;
double taxaMAC = 0.0;

// valor inicial dos níveis deve corresponder ao valor inicial de transmissão do rádio
// que é definido no omnetpp.ini
int vetorNivelPotenciaNo[] = {-1, 0, 0, 0, 0, 0};

int vetorNivelMACNo[] = {-1, 0, 0, 0, 0, 0};
int vetorPotencia[5];

/* 
	Este método funciona como uma interface para a estratégia que calcula a potência.
	A variável 'politica' é que determina qual estratégia será executada. Esta variável é inicializada uma única vez.
	O seu valor default é igual a zero, isto é, ele só retorna o valor de potência definido previamente no vetorPotencia (ver caso default do switch)

	As estratégias aqui definidas partem do mesmo princípio que é explicado abaixo.
	O vetor 'vetorNivelPotenciaNo' guarda a informação da potência de um nó.
	Este vetor tem tamanho igual ao número de nós, assim associamos o endereço do nó à posição no vetor.
	O nó sink, endereço 0, tem como valor -1 como default.
	Cada nó é representado em uma posição que tem como valor o indice da potência correspondente no vetorPotencia.
	O parâmetro 'variacao' pode assumir os valores -1, 0, 1.
	Estes valores serão usados para incrementar ou decrementar o índice que indica a potência de determinado nó.

	Desta forma com base na avaliação da taxa MAC estabelecemos níveis para a taxa MAC. 
	Com base na alternancia entre esses níveis avaliamos se a taxaMAC piorou ou melhorou e se devemos alterar a potência.

	As estratégias aqui discutidas variam na formam como elas lidam com os limites do vetor potência. São elas:

	1) policyVaryPowerBetweenRange;
	2) policyVaryPowerInCycle;
*/
int ThroughputPolicies::varyPowerLevel(int noIndex, int variacao)
{
	switch(politica)
	{
		case 1:
			return policyVaryPowerBetweenRange(noIndex, variacao);
			break;
		case 2:
			return policyVaryPowerInCycle(noIndex, variacao);
			break;
		default:
			return vetorPotencia[vetorNivelPotenciaNo[noIndex]];
	}
}

/*
	A estratégia aqui é que quando o nó atingir o extremo dos vetores, a primeira ou a última posição do vetor, 
	ele poderá manter a posição ou retornar.
	Por exemplo: se trabalhamos com 4 potências diferentes, com indices 0, 1, 2 e 3. 
	Se o nó estiver transmitindo na potência indicada pelo indice 3, ele só poderá manter a mesma potência ou passar para a potência indicada pelo indice 2.
*/
int ThroughputPolicies::policyVaryPowerBetweenRange(int noIndex, int variacao)
{
	int indexPotenciaAnterior = vetorNivelPotenciaNo[noIndex];
	int potencia = vetorPotencia[indexPotenciaAnterior];

	int indexPotenciaAtual = indexPotenciaAnterior + variacao;

	if( (indexPotenciaAtual >=0) && (indexPotenciaAtual < maxIndicePotencia)){
		vetorNivelPotenciaNo[noIndex] = indexPotenciaAtual;
		potencia = vetorPotencia[indexPotenciaAtual];
	}

	return potencia;
}

/*
	Neste caso, é implementado algo semelhante a um contador cíclico (operador resto aritmético).
	Podemos dizer aqui que a potência segue em círculos para a direita ou para a esquerda.
	Por exemplo, se ela estiver transmitindo na potência indicada pela posição 3, e a variação indicar incremento da força,
	o calculo pode retornar a potência da posiçao 0, já que não existe posição 4.

	Como o valor do indice também pode ser decrementado, a variável temporária tmp assume o valor -1 em alguns casos.
	Por isso foi adícionado a condição "if(tmp < 0)	tmp = maxIndicePotencia - 1"
	Observe que "maxIndicePotencia - 1" indica a última posição válida do vetor potência, então:
		(maxIndicePotencia - 1) % maxIndicePotencia = (maxIndicePotencia - 1)
	Assim quando tmp == -1 ou tmp < 0, o indice assume o valor da última posição válida do vetor potência.
*/
int ThroughputPolicies::policyVaryPowerInCycle(int noIndex,int variacao)
{
	int indexPotenciaAnterior = vetorNivelPotenciaNo[noIndex];
	int tmp = indexPotenciaAnterior + variacao;
	if(tmp < 0)	tmp = maxIndicePotencia - 1;

	int indexPotenciaAtual = tmp % maxIndicePotencia;
	vetorNivelPotenciaNo[noIndex] = indexPotenciaAtual;

	int potencia = vetorPotencia[indexPotenciaAtual];
	return potencia;
}

void ThroughputPolicies::startup()
{

	taxa = par("taxa");
	isSink = par("isSink");

	// Indica a estratégia (ou política) adotada para variar a potência de transmissão
	politica = par("politica");

	// Indica a última posição do vetor Potência a ser considerado
	// Se maxIndicePotencia = 3, significa que a variação da potência só vai ocorrer entre -10dBm (posição 0) e -20dBm (posição 3)
	// veja a inicialização do vetorPotencia logo abaixo
	maxIndicePotencia = par("maxIndicePotencia");
	maxIndicePotencia = (maxIndicePotencia > 1) && (maxIndicePotencia <= 5) ? maxIndicePotencia : 5;

	CCAthreshold = par("CCAthreshold");
	CCAthreshold2 = par("CCAthreshold2");

	// Este trecho de código precisa ser mais flexível.
	// Como informar para a camada de aplicação quais os valores que a potência de transmissão pode assumir?
	// Estes valores são informados para a camada física.
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
	trace() << "Inicio"<<SELF_NETWORK_ADDRESS << "  politica  " << politica << "  maxIndicePotencia  " << maxIndicePotencia;
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
void ThroughputPolicies::handleRadioControlMessage(RadioControlMessage *radioMsg)
{
	switch (radioMsg->getRadioControlMessageKind()) {
		case CARRIER_SENSE_INTERRUPT:
//			trace() << "CS Interrupt received! current RSSI value is: " << radioModule->readRSSI();
                        break;
	}
}

void ThroughputPolicies::finishSpecific() {
	declareOutput("Packets reception rate");
	declareOutput("Packets loss rate");

	trace()<<"Pacotestransmitidospor "<<SELF_NETWORK_ADDRESS<<" = "<<getPacketCount(atoi(SELF_NETWORK_ADDRESS));

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

int ThroughputPolicies::getPacketCount(int node){
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

void ThroughputPolicies::countTransmitions(){
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

int ThroughputPolicies::handleControlCommand(cMessage * msg){

	double taxaMAC = 0.0;
	// double taxa = 0.0; // teste de taxa
	int indexNO = atoi(SELF_NETWORK_ADDRESS);
	int variacao = 0; // por padrao a potencia nao deve variar

	if((indexNO) >= 1 && (indexNO <= 5)){ // garantir que o index No esteja dentro deste range
		CrossLayerMsg *cmd = check_and_cast <CrossLayerMsg*>(msg);
		taxaMAC = cmd->getTaxaMAC();

		int nivelAnterior = vetorNivelMACNo[indexNO];
		int nivelClassificado = nivelAnterior;
// 		================= CONFIGURAÇÃO PARA PACKET_RATE 10 =================
		if (taxaMAC <= 40 && ( packet_rate ==10  ) ) { 
			nivelClassificado = 0;
			variacao = -1; // aqui o nivel incrementa de qualquer jeito
		}
		else if (taxaMAC < 70 && ( packet_rate == 10 ) ) {
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
		}
		else if (taxaMAC < 90 && ( packet_rate == 10) ) {
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
		}
		else if (taxaMAC >= 90 && (packet_rate == 10) ){
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
		}
// 		================= CONFIGURAÇÃO PARA PACKET_RATE 15 =================
		else if ( taxaMAC <= 40 &&  (packet_rate ==15) ) { 
			nivelClassificado = 0;
			variacao = -1;
		} 
		else if (taxaMAC < 70 && (packet_rate ==15)  ) {
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
		}
		else if (taxaMAC < 90 && (packet_rate ==15)  ) {
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
		}
		else if (taxaMAC >= 90 && (packet_rate ==15)  ) {
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
		}
//		================= CONFIGURAÇÃO PARA PARA PACKET_RATE 25 =================
		else if ( taxaMAC <= 40 &&  (packet_rate == 25) ) { 
			nivelClassificado = 0;
			variacao = -1;
		}
		else if (taxaMAC < 70 && (packet_rate == 25)  ) {
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
		}

		else if (taxaMAC < 90 && (packet_rate == 25)  ) {
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
		}

		else if (taxaMAC >= 90 && (packet_rate == 25)  ) {
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
		}

		// funcao que varia a potencia
		// varyPowerLevel(int noIndex, int nivelAnterior, int variacao)
		int potencia = varyPowerLevel(indexNO, variacao);
		trace() << "POTENCIA_INFO   " << potencia;
        trace() << "TAXAMAC_INFO    " << taxaMAC;
		toNetworkLayer(createRadioCommand(SET_TX_OUTPUT,potencia));
		vetorNivelMACNo[indexNO] = nivelClassificado;

		delete cmd;
	} 

	 return 1;
}
