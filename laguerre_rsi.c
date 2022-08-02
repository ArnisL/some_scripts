// default Dampen = .5
float LaguerreRSI(var Dampen, var Close){
	vars L0 = series(0);
	vars L1 = series(0);
	vars L2 = series(0);
	vars L3 = series(0);
	vars CU = series(0);
	vars CD = series(0);
	var rsi = 0;

	L0[0]=(1-Dampen)*Close+Dampen*L0[1];
	L1[0]=-Dampen*L0[0]+L0[1]+Dampen*L1[1];
	L2[0]=-Dampen*L1[0]+L1[1]+Dampen*L2[1];
	L3[0]=-Dampen*L2[0]+L2[1]+Dampen*L3[1];
	CU[0]=0; CD[0]=0;

	if (L0[0]>L1[0]) {
		CU[0]=L0[0]-L1[0];
	}else{
		CD[0]=L1[0]-L0[0];
	}

	if (L1[0]>L2[0]) {
		CU[0]=CU[0]+L1[0]-L2[0];
	}else{
		CD[0]=CD[0]+L2[0]-L1[0];
	}

	if (L2[0]>L3[0]) {
		CU[0]=CU[0]+L2[0]-L3[0];
	}else{
		CD[0]=CD[0]+L3[0]-L2[0];
	}

	if (CU[0]+CD[0]>0||CU[0]+CD[0]<0) {
		rsi=CU[0]/(CU[0]+CD[0]);
	}

	return rsi;
}
