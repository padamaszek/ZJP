#include<stdio.h>

double max(double a,double b)
{
if(a<b){
return b;
}
else{
return a;
}

}

double max_tab(double *tab,int ilosc)
{
if(ilosc == 1)
{
return tab[0];
}
else{
return max(max_tab(tab,ilosc-1),tab[ilosc-1]);
}

}

int main()
{
	int ilosc,i;
	printf("Podaj ilosc liczb ");
	scanf("%d",&ilosc);
	double tab[ilosc];
	for(i=0; i<ilosc;i++)
	{
	scanf("%lf",&tab[i]);
	}
double wynik = max_tab(tab,ilosc);
printf("%lf\n",wynik);
}
