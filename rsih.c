var RSIH(vars Data, int Length) 
{
  var CU = 0, CD = 0;
  int i;
  for(i=1; i<Length; i++) {
    var D = Data[i-1]-Data[i];
    var Hann = 1-cos(2*PI*i/(Length+1));
    if(D > 0) CU += Hann*D;
    else if(D < 0) CD -= Hann*D;
  }
  if(CU+CD != 0)
    return (CU-CD) / (CU+CD);
  else return 0;
}
