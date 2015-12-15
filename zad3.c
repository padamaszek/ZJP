#include<stdio.h>
#include<math.h>

/*
wiel(i){
if(i==n) then 0
else a[i] + x + wiel(i+1)

n - dlugosc wielomianu
wywolanie: wiel(0);
 */
double wspol(double *tab,int n,double x)
{
if(n == 0){
return 0;
}else{
return tab[n-1] * pow(x,n-1) + wspol(tab,n-1,x);
}
}
int main()
{
	int ilosc,i;
	double x,wynik;
	printf("Podaj ilosc liczb ");
	scanf("%d",&ilosc);
	double a[ilosc];
	for(i=0; i<ilosc;i++)
	{
	scanf("%lf",&a[i]);
	}
	printf("Podaj liczbe rzeczywista x ");
	scanf("%lf",&x);
	wynik = wspol(a,ilosc,x);
	printf("%lf\n",wynik);
}
