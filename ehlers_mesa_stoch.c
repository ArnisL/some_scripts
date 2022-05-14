// default Length = 20, FilterLength = 48
float EhlersStochMESA(int Length, var* Price, int FilterLength){	
	var pi = 2 * asin(1);
	var* HP = series(HighPass2(Price, FilterLength));
	var a1 = exp(-1.414 * 3.14159 / 10);
	var b1 = 2 * a1 * cos(1.414 * pi / 10);
	var c2 = b1;
	var c3 = -a1 * a1;
	var c1 = 1 - c2 - c3;
	
	var* Filt = series(0);
	Filt[0] = c1 * (HP[0] + HP[1]) / 2 + c2 * Filt[1] + c3 * Filt[2];
	var HighestC = Filt[0];
	var LowestC = Filt[0];

	var i;
	for(i = 0; i < Length-1; i++) {
		if (Filt[i] > HighestC) HighestC = Filt[i];
		if (Filt[i] < LowestC) LowestC = Filt[i];
	}

	var* Stoc = series(0);
	
	if ((HighestC - LowestC) != 0) {
		Stoc[0] = (Filt[0] - LowestC) / (HighestC - LowestC);
	}
	
	var* MESAStochastic = series(0);
	MESAStochastic[0] = c1 * (Stoc[0] + Stoc[1]) / 2 + c2 * MESAStochastic[1] + c3 * MESAStochastic[2];
	
	return MESAStochastic[0];
}
