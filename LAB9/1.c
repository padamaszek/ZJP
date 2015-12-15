#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 15000
#define MLD 1000000

int tab[MAX];

int indeks(int i, int n) 
{
    if (i >= n || i < 0) {
        printf("Index poza zakresem \n");
        exit(1);
        return 0;
    }
    else return i;
}

void bubblesortIndeks(int size)
{
    int i, j, temp;
    for (i = 0; i<size-1; i++)
    {
        for (j=0; j<size-1-i; j++)
        {
            if (tab[j] > tab[j+1])
            {
                temp = tab[j+1];
                tab[j+1] = tab[j];
                tab[j] = temp;
            }
        }
     }
}

void bubblesort(int size)
{
    int i, j, temp;
    for (i = 0; i<size-1; i++)
    {
        for (j=0; j<size-1-i; j++)
        {
            if (tab[indeks(j, MAX)] > tab[indeks(j+1, MAX)])
            {
                temp = tab[indeks(j+1, MAX)];
                tab[indeks(j+1, MAX)] = tab[indeks(j, MAX)];
                tab[indeks(j, MAX)] = temp;
            }
        }
     }
}

void macierze(int *tab,int n, int k){
int size = n*k;
int tab1[size];
int i;
for(i=0;i<n;i++){
for(i=0;i<k;i++){
tab1[i]

}
}

}


int main()
{
	int i;

	for (i = MAX -1; i >= 0; i--) {
        tab[i] = i;
    }
	
	struct timespec tp0, tp1, tp01, tp02;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    bubblesort(MAX);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
	    double czas_losowy=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf("Czas dla sortowania ze sprawdzaniem: %lf\n", czas_losowy);


    for (i = MAX - 1; i >= 0; i--) {
        tab[i] = i;
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp01);
    bubblesortIndeks(MAX);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp02);
    double czas_losowy2=(tp02.tv_sec+tp02.tv_nsec/MLD)-(tp01.tv_sec+tp01.tv_nsec/MLD);
    printf("Czas dla sortowania bez sprawdzania: %lf\n", czas_losowy2);
    printf("Różnica dla 100000 elementów w tablicy: %lf \n", (czas_losowy2/czas_losowy)*100);
    printf("%lf",czas_losowy/czas_losowy2);
	
	
	return 0;
}
