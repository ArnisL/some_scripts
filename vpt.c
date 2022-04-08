function VPT(var Volume, vars Close) {
	vars vpt = series(0, 2);
	vpt[0] = vpt[1] + Volume * ((Close[0] - Close[1])/Close[1]);
	return vpt[0];
}
