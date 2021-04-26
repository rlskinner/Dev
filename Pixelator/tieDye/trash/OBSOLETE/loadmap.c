main()
{
	char	sys[1024];
	sprintf( sys, "loadmap %s\0", "data/rainbow.map" );
	system( sys );
}
