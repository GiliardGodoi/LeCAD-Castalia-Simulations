enum ThroughputPriorityCommandDef {
	TAXAMAC_INFO = 1;
	BUFFER_INFO = 2;
}

message ThroghputPriorityMsg {
    int type enum (ThroughputPriorityCommandDef);
	double taxaMAC = 0;
    double bufferState = 0;
}