enum Basic802154CommandDef {
	SET_INTERVAL = 1;
	SET_OTHER = 2;
}

message Basic802154ControlCommand {
	int basic802154CommandKind enum (Basic802154CommandDef);
	double parameter = 0;
}
