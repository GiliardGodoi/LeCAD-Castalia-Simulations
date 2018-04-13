enum ThroughputTestCommandDef {
	SET_RATE = 1;
	SET_PRIORITY = 2;
}

message ThroughputTestControlCommand {
	int throughputTestCommandKind enum (ThroughputTestCommandDef);
	double parameter = 0;
}
