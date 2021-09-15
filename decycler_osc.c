var DecyclerOscillator(var* Close, var HPPeriod1, var HPPeriod2)
{
	return HighPass2(Close, HPPeriod2) - HighPass2(Close, HPPeriod1);
}