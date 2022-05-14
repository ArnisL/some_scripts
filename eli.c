// Ehlers Leading
// alpha1 .25
// alpha2 .33
// src hl2
float ELI(var alpha1, var alpha2, vars src) {
	vars lead = series(.0);
	lead[0] = 2 * src[0] + (alpha1 - 2) * src[1] + (1 - alpha1) * lead[1];
	
	vars leadingIndicator = series(.0);
	leadingIndicator[0] = 
		alpha2 * lead[0] + 
		(1 - alpha2) * leadingIndicator[1];
	
	return leadingIndicator[0];
}
