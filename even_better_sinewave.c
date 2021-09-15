var EvenBetterSinewave(vars Close, var HPLength, SSFLength)
{
	var Wave;
	var Pwr;
		
	var* HP = series(HighPass1(Close, HPLength), 2);
	if (HP[0] == 0) HP[0] = 1;
	
	var* Filt = series(Smooth(HP, SSFLength), 10);
	Wave = SMA(Filt, 3);
	Pwr = (Filt[0]*Filt[0] + Filt[1]*Filt[1] + Filt[2]*Filt[2]) / 3;
	
	return Wave / sqrt(Pwr);
}