function KVO(var High, var Low, var Close, var Volume){
	vars hlc = series((High + Low + Close) / 3);	
	vars cumVol = series(0, 2);
	cumVol[0] = cumVol[1] + Volume;
	var hlcChange = hlc[0] - hlc[1];
	var sv = 0;
	if (hlcChange >= 0) sv = Volume;
	else sv = -Volume;
	
	var kvo = EMA(sv, 34) - EMA(sv, 55);
	//var sig = EMA(kvo, 13);
	return kvo;
}
