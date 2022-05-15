float ACDI(var Close, var High, var Low, var Volume){
	vars ad = series(0);
	var clv;
	if ((High - Low) == 0) {
		clv = ((Close - Low) - (High - Close));
	} else {
		clv = ((Close - Low) - (High - Close)) / (High - Low);
	}
	
	var cmfv = clv/10000 * Volume;
	ad[0] = ad[1] + cmfv;
	return ad[0];
}
