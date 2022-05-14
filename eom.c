float EOM(var Length, vars High, vars Low, var Volume) {
	var div = 10000000000;
	var eom = SMA(
		series(
			div * (
				(High[0]+Low[0])/2 - (High[1]+Low[1])/2
			) * (High[0] - Low[0]) / Volume
		),	Length
	);
	return eom;
}
