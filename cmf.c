function CMF(var Period, var High, var Low, var Close, var Volume) {
	var ad = ((2*Close-Low-High)/(High-Low))*Volume;
	return Sum(series(ad), Period) / Sum(series(Volume), Period)*100;
}
