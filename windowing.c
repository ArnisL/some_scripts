vars triangle(vars Data, int Length)
{
  vars Out = series(0,Length);
  int i;
  for(i=0; i<Length; i++)
    Out[i] = Data[i] * ifelse(i<Length/2,i+1,Length-i);
  return Out;
}

vars hamming(vars Data, int Length, var Pedestal)
{
  vars Out = series(0,Length);
  int i;
  for(i=0; i<Length; i++)
    Out[i] = Data[i] * sin(Pedestal+(PI-2*Pedestal)*(i+1)/(Length-1));
  return Out;
}

vars hann(vars Data, int Length)
{
  vars Out = series(0,Length);
  int i;
  for(i=0; i<Length; i++)
    Out[i] = Data[i] * (1-cos(2*PI*(i+1)/(Length+1)));
  return Out;
}

// TODO: check out Blackman window
// https://en.wikipedia.org/wiki/Window_function