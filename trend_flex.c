var TrendFlex(vars Data,int Period)
{
	var a1,b1,c1,c2,c3,Slope,DSum;
	vars Filt = series(Data[0]), MS = series(0);
	int i;
	
//Gently smooth the data in a SuperSmoother
	a1 = exp(-1.414*2*PI/Period);
	b1 = 2*a1*cos(1.414*PI/Period);
	c2 = b1;
	c3 = -a1*a1;
	c1 = 1-c2-c3;
	Filt[0] = c1*(Data[0]+Data[1])/2 + c2*Filt[1] + c3*Filt[2];

//Sum the differences
	for(i=1,DSum=0; i<=Period; i++)
		DSum += Filt[0] - Filt[i];
	DSum /= Period;
	
//Normalize in terms of Standard Deviations
	MS[0] = .04*DSum*DSum + .96*MS[1];
	if(MS[0] > 0.) return DSum/sqrt(MS[0]);
	else return 0.;
}
