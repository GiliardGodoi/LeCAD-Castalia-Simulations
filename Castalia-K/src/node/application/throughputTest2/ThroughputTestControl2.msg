enum ThroughputTest2CommandDef {
	SET_RATE = 1;
	SET_PRIORITY = 2;
}

message ThroughputTest2ControlCommand {
	int throughputTestCommandKind enum (ThroughputTest2CommandDef);
	double parameter = 0;
}
