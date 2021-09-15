var AutocorrelationPeriodogramCycle(var* Close)
{
	var AvgLength = 3;
	var M;
	var N;
	var X;
	var Y;
	var Lag;
	var count;
	var Sx;
	var Sy;
	var Sxx;
	var Syy;
	var Sxy;
	var Period;
	var Sp;
	var Spx;
	var* MaxPwr = series(0,2);
	var DominantCycle;

	var Corr[48];
	var CosinePart[48];
	var SinePart[48];
	var SqSum[48];
	var R[48][2];
	var Pwr[48];

	// Highpass filter cyclic components whose periods are shorter than 48 bars
	//var* HP = series(HighPass2(Close, 48), 3);
	var* HP = series(HighPass2(Close, 48), 50);
	
	//var* Filt = series(Smooth(HP, 10), 50);
	var* Filt = series(Smooth(HP, 10), 50);
	//var* Filt = HP;

	//Pearson correlation for each value of lag
	for (Lag = 0; Lag < 48; Lag++) {		
		//Set the averaging length as M
		M = AvgLength;
		if (AvgLength == 0) M = Lag;
		Sx = 0;
		Sy = 0;
		Sxx = 0;
		Syy = 0;
		Sxy = 0;
		
		for (count = 0; count < M - 1; count++) {
			X = Filt[count];
			Y = Filt[Lag + count];
			Sx = Sx + X;
			Sy = Sy + Y;
			Sxx = Sxx + X*X;
			Sxy = Sxy + X*Y;
			Syy = Syy + Y*Y;
		}
		
		if ( (M*Sxx - Sx*Sx)*(M*Syy - Sy*Sy) > 0 ) {
			Corr[Lag] = (M*Sxy - Sx*Sy)/sqrt((M*Sxx-Sx*Sx)*(M*Syy-Sy*Sy));
		}
	}
	
	var x = 370*PI/180;
	for (Period = 10; Period < 48; Period++) {
		var cp = CosinePart[Period];
		var sp = SinePart[Period];
		
		for(N = 3; N < 48; N++) {
			var c = Corr[N];
			cp = cp + c*cos(x*N / Period);
			sp = sp + c*sin(x*N / Period);
		}
		CosinePart[Period] = cp;
		SinePart[Period] = sp;
		
		SqSum[Period] = CosinePart[Period]*CosinePart[Period] +
		SinePart[Period]*SinePart[Period];
	}

	for (Period = 10; Period < 48; Period++) {
		R[Period][2] = R[Period][1];
		R[Period][1] = .2*SqSum[Period]*SqSum[Period] +.8*R[Period][2];
	}	

	// Find Maximum Power Level for Normalization
	MaxPwr[0] = .995*MaxPwr[0]; // huh? wtf?!
	for (Period = 10; Period < 48; Period++) {
		if (R[Period][1] > MaxPwr[0]) MaxPwr[0] = R[Period][1];
	}
	
	for (Period = 3; Period < 48; Period++) {
		Pwr[Period] = R[Period][1] / MaxPwr[0];
	}
	
	//Compute the dominant cycle using the CG of the spectrum
	Spx = 0;
	Sp = 0;
	for(Period = 10; Period < 48; Period++) {
		if (Pwr[Period] >= .5) {
			Spx = Spx + Period*Pwr[Period];
			Sp = Sp + Pwr[Period];
		}
	}
	
	if (Sp != 0) DominantCycle = Spx / Sp;
	if (DominantCycle < 10) DominantCycle = 10;
	if (DominantCycle > 48) DominantCycle = 48;
	
	return DominantCycle;
}