#include<stdio.h>

int suma(int *tab,int x)
{
if(x == 0){
return 0;
}
else{
return tab[x-1]+suma(tab,x-1);
}
}

int main()
{
	int ilosc,i;
	printf("Podaj ilosc liczb ");
	scanf("%d",&ilosc);
	int tab[ilosc];
	for(i=0; i<ilosc;i++)
	{
	scanf("%d",&tab[i]);
	}
	int sum = suma(tab,ilosc);
	printf("%d\n",sum);
}
