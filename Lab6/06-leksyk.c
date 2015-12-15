// ANALIZATOR LEKSYKALNY
//
// Wczytuje ze standardowego wej¶cia ci±g znaków.
// Drukuje na standardowe wyj¶cie podzia³ tego ci±gu na leksemy.


#include<stdio.h>
#include<stdlib.h>

#define max_dl_leksemu 100

typedef enum { FALSE = 0, TRUE = 1 }  Boolean;

typedef enum { STAN_POCZ   =  0,
               STAN_A      =  1,
               STAN_AD     =  2,
               STAN_ADA      =  3,
               STAN_ASI     =  4,
               STAN_K   =  5,
               STAN_KA  =  6,
               STAN_KAM    =  7,
               STAN_KAMI  =  8,
               STAN_KAMIL  =  9,
	       STAN_AS = 10,
//
               
               STAN_KAMILA = 11,
               STAN_ADAM = 12,
               STAN_NIEOKR = 13,
	       STAN_ASIA = 14   }  Stany;

typedef enum { ZNAK_A      =  0,
               ZNAK_D      =  1,
               ZNAK_M      =  2,
               ZNAK_S      =  3,
               ZNAK_I      =  4,
               ZNAK_K     =  5,
               ZNAK_L     =  6,
//
               ZNAK_NIEOKR = 7  }  Znaki;

typedef enum { MEZCZYZNA  = 0,
               KOBIETA    = 1
               }  Jednostki;

struct leksem
  {
    Jednostki jed;             // rodzaj leksemu
    int dlug;                  // d³ugo¶æ leksemu  ( 1 <= dlug <= max_dl_leksemu )
    char zaw[max_dl_leksemu];  // chary sk³adaj±ce siê na leksem
  };


void  blad (char s[], char ch)
    // sygnalizacja b³êdu; drukuje napis  s  i char  ch
    // a nastêpnie siê zatrzymuje
  {
    printf ("!!! %s  '%c' !!!\n\n", s, ch);
    exit(1);
  }


Znaki  kategoria (char ch)
    // ta funkcja grupuje chary z wej¶cia w elementy typu  Znaki ;
    // to znaczy zapomina o ró¿nicy miêdzy literami ma³ymi i du¿ymi,
    // wszystkim cyfrom przypisuje  ZNAK_CYF ,
    // nielegalnym znakom przypisuje  ZNAK_NIEOKR
  {
    if (ch == 'a' || ch == 'A')  return ZNAK_A;     else
    if (ch == 'd' || ch == 'D')  return ZNAK_D;     else
    if (ch == 'm' || ch == 'M')  return ZNAK_M;     else
    if (ch == 's' || ch == 'S')  return ZNAK_S;     else
    if (ch == 'i' || ch == 'I')  return ZNAK_I;     else
    if (ch == 'k' || ch == 'K')  return ZNAK_K;     else
    if (ch == 'l' || ch == 'L')  return ZNAK_L;     else
    else  return ZNAK_NIEOKR;
  }


Stany  tab_symb[11][8]; 
  // -- tabela symboli czyli zakodowany automat; indeksowana stanami
  // od STAN_POCZ do STAN_KAMIL oraz znakami od ZNAK_A do ZNAK_NIEOKR

char  wejscie;
  // char przeczytany na zapas z wej¶cia


void  leks (struct leksem* lk)
    // zasadnicza funkcja programu;
    // jej wywo³anie powoduje wczytanie odpowiedniej liczby charów z
    // wej¶cia i z³o¿enie z nich leksemu (lub sygnalizacjê b³êdu);
    // zak³adamy, ¿e w momencie wywo³ania w zmiennej globalnej  wejscie
    // jest ju¿ wczytany jeden char z wej¶cia;
    // po zakoñczeniu dzia³ania tej funkcji w tej zmiennej jest ju¿
    // wczytany jeden char na zapas
  {
    Stany  q, q1;
    Znaki  z;
    Boolean  koniec;
    q1 = STAN_POCZ; lk->dlug = 0; koniec = FALSE;
    do
      { z = kategoria(wejscie);
        q = q1; q1 = tab_symb[q][z];
        if (q1 == STAN_NIEOKR)  { /* b³±d */ q1 = q; koniec = TRUE; }  else
        if (q1 > STAN_AS)
          {   /* koniec leksemu */
            lk->zaw[lk->dlug] = wejscie; lk->dlug++; scanf("%c", &wejscie);
              /* Uwaga: brak sygnalizacji przepe³nienia tablicy  lk->zaw  */
            koniec = TRUE;
          }
        else
          { lk->zaw[lk->dlug] = wejscie; lk->dlug++; scanf("%c", &wejscie);
              /* Uwaga: brak sygnalizacji przepe³nienia tablicy  lk->zaw  */
          }
        }
    while (! koniec);
      // po zakoñczeniu powy¿szej pêtli w  q1  jest stan, na którym
      // automat zakoñczy³ dzia³anie; pozostaje sprawdziæ, czy to jest
      // stan akceptuj±cy i co akceptuj±cy
    switch (q1)
      { case STAN_POCZ   : blad("Nieoczekiwany znak", wejscie); break;
        case STAN_A      : blad("Mialo byc 'A' a jest", wejscie); break;
        case STAN_AD     : blad("Mialo byc 'AD' a jest", wejscie); break;
        case STAN_ADA      : blad("Mialo byc 'AS' a jest", wejscie); break;
        case STAN_ASI     : blad(" a jest", wejscie); break;
        case STAN_KA  : blad("Mialo byc 'KA' a jest", wejscie); break;
        case STAN_KAM    : blad("Mialo byc 'KAM' a jest", wejscie); break;
        case STAN_KAMI  : blad("Mialo byc 'KAMI' a jest", wejscie); break;
        case STAN_K   : blad("Mialo byc 'K' a jest", wejscie); break;
        case STAN_KAMIL  : lk->jed = MEZCZYZNA; break;
        case STAN_ADA  : lk->jed = KOBIETA; break;
        case STAN_KAMILA : lk->jed = KOBIETA; break;
	case STAN_ADAM : lk->jed = MEZCZYZNA; break;
	case STAN_ASIA :lk->jed = KOBIETA; break;
        case STAN_NIEOKR : blad("Nieoczekiwany znak", wejscie); break;
      }
  }


void  wydruk (struct leksem lk)
    // wydruk pojedynczego leksemu
  {
    int i;
    printf("LEKSEM:  ");
    switch (lk.jed)
      { case KOBIETA  : printf("KOBIETA      '"); break;
        case MEZCZYZNA   : printf("MEZCZYZNA   '"); break;
      }
    for (i=0; i<lk.dlug; i++)  printf("%c", lk.zaw[i]);
    printf("'\n");
  }


int main ()
  {
    //------------------------------------------------------
    // Inicjalizacja tabeli symboli:

    Stany q;  Znaki z;  struct leksem  lk;

    for (q = STAN_POCZ; q <= STAN_AS; q++)
      for (z = ZNAK_A; z <= ZNAK_NIEOKR; z++)
        tab_symb[q][z] = STAN_NIEOKR;

   
    tab_symb[STAN_POCZ][ZNAK_A] = STAN_A;
    tab_symb[STAN_POCZ][ZNAK_D] = STAN_ADA;
    tab_symb[STAN_POCZ][ZNAK_K] = STAN_OPER;
    tab_symb[STAN_POCZ][ZNAK_L] = STAN_OPER;
    tab_symb[STAN_POCZ][ZNAK_CYF] = STAN_K;
    tab_symb[STAN_POCZ][ZNAK_CIACH] = STAN_KA;
    tab_symb[STAN_POCZ][ZNAK_SP] = STAN_KAMIL;

    tab_symb[STAN_A][ZNAK_D] = STAN_AD;
    tab_symb[STAN_AD][ZNAK_M] = STAN_ADA;
    tab_symb[STAN_ADA][ZNAK_S] = STAN_ASI;
    tab_symb[STAN_ASI][ZNAK_I] = STAN_ADA;
    tab_symb[STAN_K][ZNAK_CYF] = STAN_K;

    tab_symb[STAN_KA][ZNAK_L] = STAN_KAM;
    tab_symb[STAN_KAM][ZNAK_L] = STAN_KAMI;
    tab_symb[STAN_KAMI][ZNAK_L] = STAN_KAMI;
    tab_symb[STAN_KAMI][ZNAK_CIACH] = STAN_KOMENT;

    tab_symb[STAN_KAMIL][ZNAK_SP] = STAN_KAMIL;

    //------------------------------------------------------
    // Inne inicjalizacje:

    printf("\n"); scanf("%c", &wejscie); printf("\n"); 

    //------------------------------------------------------
    // Analiza leksykalna:

     while (wejscie != '\n')  { leks(&lk); wydruk(lk); }
     printf("\n");

    //------------------------------------------------------

     return 0;
  }
