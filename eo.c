var EO(vars Data,int Length)
{
  vars Derivs = series(priceClose(0)-priceClose(2));
  var RMS = sqrt(SumSq(Derivs,Length)/Length);
  var NDeriv = Derivs[0]/RMS;
  vars IFishs = series(FisherInv(&NDeriv));
  return Smooth(IFishs,20);
}
