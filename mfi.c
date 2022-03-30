function MFI(var Period, var High, var Low, var Close, var Volume) {
	vars vol = series(Volume);	
	vars hlc = series((High + Low + Close) / 3);	
	var pos=.0;
	var neg=.0;
	var i = 0;
	for(i=0;i<Period;i++) {
		if (hlc[i] > hlc[i+1]) pos = pos + vol[i];
		if (hlc[i] < hlc[i+1]) neg = neg + vol[i];
	}
	var mfr = pos / neg;		
	var mfi = 0;
	if (1+mfr != 0) mfi = 100 - 100 / (1 + mfr);	
	return mfi;
}
