float ACDI(var Close, var High, var Low, var Volume){
	vars ad = series(0, 2);
	var clv = ((Close - Low) - (High - Close)) / (High - Low);
	var cmfv = clv * Volume;
	ad[0] = ad[1] + cmfv;
	return ad[0];
}
