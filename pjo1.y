/* Prosty Jezyk dla Obliczen -- interpreter
 * Kolejnosc przetwarzania:
 *  (1) bison pjo1.y
 *  (2) gcc -o pjo1 pjo1.tab.c
 * Wywolanie:
 *      ./pjo1
 */
     
%{
 #include <stdio.h>
 #include <stdlib.h>
 #define YYERROR_VERBOSE 1
 #define YYSTYPE int
 #define L_ZMIENNYCH 26
 
 void  yyerror (const char s[]) {
   // wywolywane przez  yyparse  w razie bledu
   printf ("!!! %s\n", s);
 }
 
 YYSTYPE  yylex (void) {  // puste
   int c;
   do  { c = getchar (); }
   while (c == ' ' || c == '\t' || c == '\n');
   if (c == EOF)  return 0;
   else  return c;
 }
 
 int pamiec[L_ZMIENNYCH], i;
 
%}
 
 %token NUM
 
%%
 
    /* Gramatyka: */
 
program:      komendy '.'                { printf("KONIEC\n"); exit(1); }
 ;
komendy:       /* puste */
            | komendy komenda
 ;
komenda:      zmienna ':' binarny ';'  { pamiec[$1] = $3;
                                           printf("BISON>      %c == %i\n",
                                                   (char)($1+'a'),
                                                   $3
                                                 );
                                           printf("UZYTKOWNIK> ");
                                         }
            | wyrazenie ';'              { printf("BISON>      == %i\n", $1);
                                           printf("UZYTKOWNIK> ");
                                         }
 ;
wyrazenie:    skladnik                   { $$ = $1; }
            | wyrazenie '=' skladnik     { if($3 == $1){$$=1;} else{$$=0;}; }
 ;
skladnik:     czynnik                    { $$ = $1; }
            | czynnik  '>' skladnik      { if($1 == 1 && $3 == 0 ){$$=0;} else{$$=1;}; }
 
;
czynnik:      atom                       { $$ = $1; }
            | czynnik 'v' atom           { if($1 == 1 || $3 == 1){$$=1;} else{$$=0;}; }
 
;
atom:         atomek                     { $$ = $1; }
            | atom '^' atomek            { if($1 == 1 && $3 == 1){$$=1;} else{$$=0;}; }
 
;
atomek:      zmienna2                    { $$ = $1; }
            | '-' atomek                 { if($2 == 1){$$=0;} else{$$=1;}; }
;
zmienna2:    zmienna                     { $$ = pamiec[$1]; }
            | '(' wyrazenie ')'          { $$ = $2; }
 ;
zmienna:      'a'                        { $$ =  0; }
            | 'b'                        { $$ =  1; }
            | 'c'                        { $$ =  2; }
            | 'd'                        { $$ =  3; }
            | 'e'                        { $$ =  4; }
            | 'f'                        { $$ =  5; }
            | 'g'                        { $$ =  6; }
            | 'h'                        { $$ =  7; }
            | 'i'                        { $$ =  8; }
            | 'j'                        { $$ =  9; }
            | 'k'                        { $$ = 10; }
            | 'l'                        { $$ = 11; }
            | 'm'                        { $$ = 12; }
            | 'n'                        { $$ = 13; }
            | 'o'                        { $$ = 14; }
            | 'p'                        { $$ = 15; }
            | 'q'                        { $$ = 16; }
            | 'r'                        { $$ = 17; }
            | 's'                        { $$ = 18; }
            | 't'                        { $$ = 19; }
            | 'u'                        { $$ = 20; }
            | 'v'                        { $$ = 21; }
            | 'w'                        { $$ = 22; }
            | 'x'                        { $$ = 23; }
            | 'y'                        { $$ = 24; }
            | 'z'                        { $$ = 25; }
 ;
 
binarny:      '0'                        { $$ = 0; }
            | '1'                        { $$ = 1; }
 
 ;
 
/****************************************************/
%%
 
int main (void) {
 for (i=0; i<L_ZMIENNYCH; i++)  pamiec[i] = 0;
 printf("UZYTKOWNIK> ");
 return yyparse ();
}
