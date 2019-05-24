enum CrossLayerCommandDef {
	TAXAMAC_INFO = 1;
	BUFFER_INFO = 2;
}

message CrossLayerMsg {
    int type enum (CrossLayerCommandDef);
	double taxaMAC = 0;
    double bufferState = 0;
}