float VO(int ShortPeriod, int LongPeriod, vars VolumeSeries) {
	var s = EMA(VolumeSeries, ShortPeriod);
	var l = EMA(VolumeSeries, LongPeriod);
	return ((s - l) / l) * 100;
}
