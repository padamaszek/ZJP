#include<stdio.h>
#define DUZO 20000
#define NIL -1

typedef int adres;

typedef struct{
char znak;
adres dalej;

}wezel;

wezel sterta[DUZO];
adres wolne;

void sterta_init(){
int i=0;
for(i = 1; i<DUZO; i++){
sterta[i-1].dalej = i;
}
sterta[i-1].znak = NIL;
wolne = 0;
}

/* 
wszystkie wezly tablicy
sterta inicjuje na liste
adres pierwszego wpisuje
do zmiennej wolne
*/

adres alok(){
if(wolne == NIL){
printf("brak pamieci");
return 0;
}else{
adres pom = wolne;
wolne = sterta[wolne].dalej;
return pom;
}
/*
oddaje wartosc za wolne 
a wartosc wolne poprawia
tak zeby wskazywala
na nastepny w liscie
*/
}

void dealok(adres a){
if(a == NIL){
printf("dealokacja NIL-a");
}else{
sterta[a].dalej = wolne;
wolne = a;
}

/*
dolacza wezel o adres a
do listy wolne
*/
}
void przepisz(adres x,adres y){
sterta[y].licznik ++;
sterta [x].licznik --;
if(sterta[x].licznik == 0){
...
x=y;
}
}
int main(){


return 0;
}
