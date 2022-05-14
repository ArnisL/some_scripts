float EFI(int Period, var Close, var Volume) {
  vars CloseSeries = series(Close);
  var change = CloseSeries[0] - CloseSeries[1];
  var efi = EMA(change * Volume, Period);
  return efi;
}
