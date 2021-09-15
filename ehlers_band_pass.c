#include <rad_trig.c>

var* EhlersBandPass(var* Close, var Period, var Bandwidth)
{
	var alpha2 = 0;
	var* HP = series(0,3);
	var gamma1 = 0;
	var alpha1 = 0;
	var beta1 = 0;
	var* BP = series(0,3);
	var* Peak = series(0,2);
	var* Signal = series(0,2);
	var* Trigger = series(0,2);
	var result[2];
	
	alpha2 = 
		 (rcos(.25*Bandwidth*360 / Period) + rsin(.25*Bandwidth*360 / Period) - 1) / 
			 rcos(.25*Bandwidth*360 / Period);

	HP[0] = (1 + alpha2 / 2)*(Close[0] - Close[1]) + (1- alpha2)*HP[1];
	beta1 = rcos(360 / Period);
	
	gamma1 = 1 / rcos(360*Bandwidth / Period);

	alpha1 = gamma1 - sqrt(gamma1*gamma1 - 1);
	
	BP[0] = .5*(1 - alpha1)*
		(HP[0] - HP[2]) + beta1*(1 + alpha1)*BP[1] - alpha1*BP[2];

	if (Bar == 1 || Bar == 2) BP[0] = 0;
	Peak[0] = .991*Peak[1];
	if (abs(BP[0]) > Peak[0]) Peak[0] = abs(BP[0]);
	if (Peak[0] != 0) Signal[0] = BP[0] / Peak[0];
	
	alpha2 = (rcos(1.5*Bandwidth*360 / Period) +
		rsin(1.5*Bandwidth*360 / Period) - 1) / 
		rcos(1.5*Bandwidth*360 / Period);
	
	Trigger[0] = 
		(1 + alpha2 / 2)*
		(Signal[0] - Signal[1]) + (1- alpha2)*Trigger[1];
	
	result[0] = Signal[0];
	result[1] = Trigger[0];
	return result;
}

// var* EhlersBandPass(var* Close, var DominantCycle, var Bandwidth)
// {
	// var* BP = series(0,3);
	// var* Peak = series(0,2);
	// var* Signal = series(0,2);
	// var* Lead = series(0,2);
	// var* LeadPeak = series(0,2);
	// var* LeadSignal = series(0,2);
	
	// DominantCycle = .81 * DominantCycle;

	// var* HP = series(0,2);
	// var result[4];

	// HP[0] = HighPass2(Close, 50);

	// var beta1 = rcos(360 / DominantCycle);
	// var gamma1 = 1 / rcos(360*Bandwidth / DominantCycle);
	// var alpha2 = gamma1 - sqrt(gamma1*gamma1 - 1);

	// BP[0] = .5*(1 - alpha2)*
		// (HP[0] - HP[2]) + beta1*(1 +	alpha2)*BP[1] - alpha2*BP[2];

	// if (Bar == 1 || Bar == 2) BP[0] = 0;
	// Peak[0] = .994*Peak[1];
	// if (abs(BP[0]) > Peak[0]) Peak[0] = abs(BP[0]);
	// if (Peak[0] != 0) Signal[0] = BP[0] / Peak[0];

	// Lead[0] = 
		// 1.5*(Signal[0] + Signal[1] - Signal[2] - Signal[3]) / 4;

	// LeadPeak[0] = .94*LeadPeak[1];

	// if (abs(Lead[0]) > LeadPeak[0]) LeadPeak[0] = abs(Lead[0]);
	// if (LeadPeak[0] != 0) LeadSignal[0] = .8 * Lead[0] / LeadPeak[0];

	// result[0] = Signal[0];
	// result[1] = .9*Signal[1];
	// result[2] = Lead[0];
	// result[3] = LeadSignal[0];
	// return result;
// }