// REKURSYWNY ZSTEPUJACY ANALIZATOR SKŁADNIOWY
//
// Wczytuje ze standardowego wejscia ciag znakow oznaczajacy wyrazenie
// arytmetyczne.
// Drukuje na standardowe wyjscie drzewo rozbioru (lub komunikat
// bledu).


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define  max_il_synow  3
#define  max_szer_druku  100
#define  max_wys_druku  40

typedef enum { FALSE = 0, TRUE = 1 }  Boolean;

typedef enum {
  S = 0,
  T = 1
}  nieterminal;

typedef struct dr {
  Boolean czyterm;
  char lk;                       // o ile  czyterm = TRUE
  nieterminal ntm;               // o ile  czyterm = FALSE
  int il_syn;                    // o ile  czyterm = FALSE
  struct dr* syn[max_il_synow];  // o ile  czyterm = FALSE
}  drzewo;

//------------------------------------------------------
// POMOCNICZE:

char  leks;


Boolean  nowyleks(char c) {
    // jesli na wejsciu stoi znak  c , to go sczytuje i oddaje TRUE;
    // jesli tam stoi inny znak, to nic nie wczytuje i oddaje FALSE
  if (leks == c) {
    do { scanf("%c", &leks); }
    while ((leks < '!' || leks > '~') && leks != '\n');
    return TRUE;
  }
  else  return FALSE;
}


Boolean  blad (char s[]) {
    // sygnalizacja błędu:
    // drukuje napis  s  a następnie przerywa wykonanie programu
  printf ("\n  BLAD:  %s\n\n", s); exit(1);
  return FALSE;
}

//------------------------------------------------------
// Serce parsera:
// PO JEDNEJ PROCEDURZE REKURSYWNEJ NA KAZDY NIETERMINAL


Boolean  SS (drzewo* drz);
Boolean  TT (drzewo* drz);


//   <A>  ::=  y <A> <B> z  | x
Boolean  SS (drzewo* drz) {
  drzewo drz1, drz2;
  if (nowyleks('a'))
    if (SS(&drz1))
     
	if (nowyleks('d')) {
          // Rozpoznalismy  b <S> d , robimy z tego drzewo:
	  drz->czyterm = FALSE;
	  drz->ntm = S;
	  drz->il_syn = 3;

	  drz->syn[0] = (drzewo*)malloc(sizeof(drzewo));
	  drz->syn[0]->czyterm = TRUE;
	  drz->syn[0]->lk = 'a';

          drz->syn[1] = (drzewo*)malloc(sizeof(drzewo));
          *(drz->syn[1]) = drz1;

	  drz->syn[2] = (drzewo*)malloc(sizeof(drzewo));
	  drz->syn[2]->czyterm = TRUE;
	  drz->syn[2]->lk = 'd';

	  return TRUE;
	}
        else  return blad("a <S> ??? -- oczekiwalem 'd' ");
      else  return blad("a  ??? -- oczekiwalem <S> ");
  else
    if (TT(&drz2)) {
      // Rozpoznalismy  x , robimy z niego drzewo:
        drz->czyterm = FALSE;
	drz->ntm = S;
	drz->il_syn=1;
      
      drz->syn[0] = (drzewo*)malloc(sizeof(drzewo));
      *(drz->syn[0]) = drz2;

      return TRUE;
    }
    else  return FALSE;
}


//   <T>  ::=  b <T> c |  e
Boolean  TT (drzewo* drz) {
  drzewo drz1;
  if (nowyleks('b'))
   if (TT(&drz1))
    if (nowyleks('c')) {
      // Rozpoznalismy  w <T> , robimy z tego drzewo:
      drz->czyterm = FALSE;
      drz->ntm = T;
      drz->il_syn = 3;

      drz->syn[0] = (drzewo*)malloc(sizeof(drzewo));
      drz->syn[0]->czyterm = TRUE;
      drz->syn[0]->lk = 'b';

      drz->syn[1] = (drzewo*)malloc(sizeof(drzewo));
      *(drz->syn[1]) = drz1;

      drz->syn[2] = (drzewo*)malloc(sizeof(drzewo));
      drz->syn[2]->czyterm = TRUE;
      drz->syn[2]->lk = 'c';

      return TRUE;
    } 
    else  return blad("b <T> ??? -- oczekiwalem 'c' ");
    else  return blad("b  ??? -- oczekiwalem <T> ");
    else
	if(nowyleks('e')) {
      // Rozpoznalismy tylko  e , robimy z niego drzewo:
      drz->czyterm = FALSE;
      drz->ntm = T;
      drz->il_syn = 1;

      drz->syn[0] = (drzewo*)malloc(sizeof(drzewo));
      drz->syn[0]->czyterm = TRUE;
      drz->syn[0]->lk = 'e';

      return TRUE;
    }
  else  return FALSE;
}
 
//------------------------------------------------------
// Pomocnicze: DRUKOWANIE DRZEWA

char  druk [max_szer_druku][max_wys_druku];


void  dr_drz (drzewo drz, int* szer, int* wys) {
  int  szer_syna[max_il_synow], wys_syna[max_il_synow], i,j;
  if (drz.czyterm) {
    *szer=*szer+3; *wys=1; druk[*szer-1][*wys-1] = drz.lk;
  }
  else {   // Drzewo nieterminalowe:
    *wys = 0;
    for (i=0; i<drz.il_syn; i++) {
      dr_drz (*drz.syn[i], szer, &wys_syna[i]);
      szer_syna[i] = *szer;
      if (*wys < wys_syna[i])  *wys = wys_syna[i];
    }
    switch (drz.ntm) { 
      case S : druk[*szer-1][*wys+1] = 'S'; break;
      case T : druk[*szer-1][*wys+1] = 'T'; break;
    }
    if (drz.il_syn > 0) {
      for (i=0; i<drz.il_syn; i++)
      for (j=wys_syna[i]; j<*wys+1; j++)
        druk[szer_syna[i]-1][j] = '|';
      for (i=szer_syna[0]; i<*szer-1; i++)  druk[i][*wys+1] = '-';
      for (i=0; i<drz.il_syn-1; i++)
	druk[szer_syna[i]-1][*wys+1] = ',';
    }
    *wys = *wys+2;
  }
}


void  drukuj_drzewo (drzewo drz) {
  int szer,wys,i,j;
  for (i=0; i<max_szer_druku; i++)
   for (j=0; j<max_wys_druku; j++)  druk[i][j] = ' ';
  szer=0;  dr_drz (drz, &szer, &wys);
  for (j=wys-1; j>=0; j--) {
    for (i=0; i<szer; i++)  printf("%c",druk[i][j]);
    printf("\n");
  }
  printf("\n");
}

//------------------------------------------------------
// Program główny:

int main() {
  drzewo drz;  Boolean ok;

    // Wczytanie pierwszego znaku (z pominieciem niewidocznych:
  do { scanf("%c", &leks); }
  while ((leks < '!' || leks > '~') && leks != '\n');

  ok = SS(&drz);  printf ("\n");
  if (ok && leks == '\n')  drukuj_drzewo (drz);
  else
    if (ok && leks != '\n') {
      drukuj_drzewo (drz);
      printf ("  SMIECI NA KONCU: %c\n\n", leks);
    }
    else  printf ("  NAPIS BLEDNY\n\n");

  return 0;
}
