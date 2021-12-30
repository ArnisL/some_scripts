var NET(vars Data,int Period)
{
 int i,k;
 var Num = 0;
 for(i=1; i<Period; i++)
   for(k=0; k<i; k++)
     Num -= sign(Data[i]-Data[k]);
 var Denom = .5*Period*(Period-1);
 return Num/Denom;
}
