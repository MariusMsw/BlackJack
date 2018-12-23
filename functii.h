#include <stdio.h>
#include <stdlib.h>
#include <time.h> //folosit pentru functia random
#include <string.h>//folosit pentru functia strcpy
#include "structura.c"
#include "constante.h"

int mizeaza(int);//functie care stabileste miza jucatorului curent
void test_bani(int *, int *, FILE *f); //functie care testeaza daca jucatorii mai au bani
void dealer(FILE *f, int *);//dealerul trage o carte si in functie de suma totala, face ceva
void intrebare(FILE *f);//meniul jocului
void reguli(FILE *f);//o prezentare a regulilor jocului
int carte(int, FILE *f);//genereaza o carte random
void afiseaza_carte(int, char);//afiseaza cartea
void start_joc(FILE *f);//inceputul jocului
void continuare(FILE *f, int *, int *);//intreba jucatorii daca vor sa reinceapa jocul
void citire_date();//citeste numele jucatorilor
void generare_maini(FILE *f);//genereaza 1000 de maini in fisier
void mesaj();

void mesaj()
{
    printf( "BLACKJACK\n" );
    printf( "MIHAI LIVIU MARIUS\n" );
    printf( "GRUPA 152\n" );
    printf( "FACULTATEA DE MATEMATICA SI INFORMATICA, UNIVERSITATEA DIN BUCURESTI, 2017\n" );
}

void citire_date()
{

    char *nume1;
    char *nume2;

    nume1 = (char*) malloc(20);
    nume2 = (char*) malloc(20);

    printf ( "\nNumele celor 2 jucatori\n\n" );

    printf ( "Numele jucatorului 1: " );
    fgets ( nume1, 20,stdin );
    strcpy ( J1.nume, nume1 );

    printf ( "Numele jucatorului 2: " );
    fgets ( nume2, 20, stdin);
    strcpy ( J2.nume, nume2);

    system ( "cls" );
    free ( nume1 );
    free ( nume2 );
}

void intrebare (FILE *f)//Functie care intreaba jucatorii daca vor sa continue
{

    int alegere;
    system( "cls" );
    printf( "\nApasa 1 pentru a incepe jocul." );
    printf( "\nApasa 2 pentru a vedea regulile jocului." );
    printf( "\nApasa 3 pentru a iesi din joc." );
    printf( "\nAlegere: " );
    scanf("%d", &alegere); // jucatorul alege ce sa faca

    while (( alegere < 1 ) || ( alegere > 3 )) // daca introducerea este nevalida
    {
        printf ( "\nAlegere incorecta. Va rugam alegeti 1, 2 sau 3!\n" );
        scanf ( "%d", &alegere );
    }
    system( "cls" );
    switch ( alegere )
    {
    case 1:
        start_joc( f );
        break;

    case 2:
        reguli( f );
        break;

    case 3:
        printf( "Poate alta data ne jucam. O zi buna!\n" );
        system( "pause" );
        exit(0);
    }
}

void reguli(FILE *f)
{
    char alegere;

    printf( "\n          Reguli ale jocului de BLACKJACK" );
    printf( "\n          ---------------------------" );
    printf( "\n Blackjack, cunoscut si sub numele de 21, este un joc des intalnit in cazinouri. Jocul a castigat popularitate deoarece este usor de jucat, jucatorul ce are suma cartilor 21 sau cel mai aproape de 21 castiga." );
    printf( "\nI." );
    printf( "\n         Acest program genereaza carti aleatoriu." );


    printf( "\nII." );
    printf( "\n    Fiecare carte are o valoare." );
    printf( "\n       Cartile de la 1 la 10 au fix acea valoare." );
    printf( "\n       J, Q, si K au valoarea 10." );
    printf( "\n         Asarii au fie valoarea 1, fie valoarea 11" );
    printf( "\n     Scopul jocului este sa ai suma de 21 sau cat mai aproape de aceasta.\n" );

    printf( "\nIII." );
    printf( "\n     Dupa ce ti se dau cele 2 carti, trebuie sa alegi dintre HIT, Stay, Split." );
    printf( "\n      HIT: mai iau o carte,   stay: nu mai iau carte." );
    printf( "\n    SPLIT: optiune folosita cand jucatorul are cele 2 carti primite de aceeasi valoare" );
    printf( "\n     jucatorul formand cate o mana pe fiecare carte, cele 2 maini se joaca apoi dupa regulile standard" );
    printf( "\n       Daca totalul este peste 21, ai pierdut!." );
    printf( "\n     Dar poti juca din nou.\n" );
    printf( "\nDoriti sa va intoarceti la meniul anterior?" );
    printf( "\n                  (Y/N)\n                    " );

    scanf( "%c", &alegere );

    while( ( alegere != 'Y' ) && ( alegere != 'y' ) && ( alegere != 'N' ) && ( alegere != 'n' ) ) // daca e invalid
    {
        printf( "\n" );
       // printf( "Alegere incorecta. Alegeti Y pentru DA sau N pentru NU.\n" );
        scanf( "%c", &alegere );
    }

    if( ( alegere == 'Y' ) || ( alegere == 'y' ) ) // daca da, continua. Afiseaza meniul
    {
        system( "cls" );
        intrebare( f );
    }

    else if( ( alegere == 'N' ) || ( alegere == 'n' ))//altfel, iese din program
    {
        system( "cls" );
        printf( "\nPoate alta data. O zi buna.\n" );
        exit(0);
    }
}

void afiseaza_carte(int valoare_carte_jucator_actual,char semn_carte_jucator_actual)//functia afiseaza cartea folosind valoarea si semnul citite din fisier in functia start_joc
{
    printf( " -------\n" );
    printf( "|%c    %c|\n", semn_carte_jucator_actual, semn_carte_jucator_actual);
    printf( "|  %d   |\n", valoare_carte_jucator_actual);
    printf( "|%c    %c|\n", semn_carte_jucator_actual, semn_carte_jucator_actual);
    printf( " -------\n" );

}

int carte(int suma_jucator,FILE *f)//functie care ia o carte din fisier
{

    int valoare_carte_jucator_actual;

    fscanf( f, "%d", &valoare_carte_jucator_actual );//citim din fisier valoarea
//in functie de valoarea totala a jucatorului, asarii valoarea 10 sau 1
    if ( ( suma_jucator > 11 ) && ( valoare_carte_jucator_actual == 11) )
        valoare_carte_jucator_actual = 1;
//regulile jocului de blackjack spun ca toate cartile cu valoare >11 valoarea 10
    if ( valoare_carte_jucator_actual > 11 )
        valoare_carte_jucator_actual = 10;

    return valoare_carte_jucator_actual;
}

void start_joc(FILE *f)
{

    int x = 0, dealer_total = 0;
    //x este folosit pentru a verifica daca jucatorul curent vrea sau nu sa stea
    //initialiam totalul dealerului cu 0
    static int bani_jucator_1 = 500, bani_jucator_2 = 500;//static ca sa se modifice la fiecare apelare a functiei

    char alegere;

    int totalul_jucatorului_1 = 0, totalul_jucatorului_2 = 0;//totalul jucatorilor sunt initializate cu 0

    int i = 1;//jucatorii pot primi 21 de carti de 1, aceasta variabila contorizand numarul de carti primite

    test_bani( &bani_jucator_1, &bani_jucator_2, f );//testam daca ambii jucatori mai au bani sau sunt sarantoci

    printf( "%s mai are %d lei \n", J1.nume, bani_jucator_1 );
    printf( "%s mai are %d lei \n", J2.nume, bani_jucator_2 );

    printf( "Cartile lui %s: \n", J1.nume);

    int aux = carte( totalul_jucatorului_1, f);//extragem o carte din fisier(valoarea ei)
    totalul_jucatorului_1 += aux;//o adunam la totalul jucacorului
    char semn_carte_jucator_actual;
    semn_carte_jucator_actual = fgetc(f);//extragem si semnul cartii respective
    afiseaza_carte( aux, semn_carte_jucator_actual);//afisam pe ecran
    aux = carte( totalul_jucatorului_1, f);//repetam la fiecare jucator de 2 ori asta, pentru ca la inceput se extrag cate 2 carti(vezi regulile)
    totalul_jucatorului_1 += aux;
    semn_carte_jucator_actual = fgetc(f);
    afiseaza_carte( aux, semn_carte_jucator_actual);

    printf( "Cartile lui %s: \n", J2.nume );

    aux = carte( totalul_jucatorului_2, f);
    totalul_jucatorului_2 += aux;
    semn_carte_jucator_actual = fgetc(f);
    afiseaza_carte( aux, semn_carte_jucator_actual);
    aux = carte( totalul_jucatorului_2, f);
    totalul_jucatorului_2 += aux;
    semn_carte_jucator_actual = fgetc(f);
    afiseaza_carte( aux, semn_carte_jucator_actual);
//afisam totalurile pana acum pentru ambii jucatori
    printf( "Totalul lui %s este: %d \n", J1.nume, totalul_jucatorului_1);
    printf( "Totalul lui %s este: %d \n", J2.nume, totalul_jucatorului_2);

    dealer(f, &dealer_total);//tragem o carte si pentru dealer, tot din fisier
    printf( "Dealerul are: %d \n", dealer_total);//si afisam si pentru el
//mizeaza jucatorii
    int miza_jucatorului_1 = mizeaza(bani_jucator_1);
    int miza_jucatorului_2 = mizeaza(bani_jucator_2);

    while ( i <= 21 )
    {
        x = 0;

        if (totalul_jucatorului_1 == 21)//daca primul jucator are 21, a castigat, celalalt  a pierdut
        {

            printf( "%s a castigat!\n", J1.nume );
            bani_jucator_1 += miza_jucatorului_1;
            dealer_total = 0;
            bani_jucator_2 -= miza_jucatorului_2;
            system( "pause" );
            system( "cls" );
            start_joc(f);
        }

        if ( totalul_jucatorului_2 == 21 )//daca al doilea a castgat, celalalt a pierdut
        {

            printf( "%s a castigat!\n", J2.nume );
            bani_jucator_2 += miza_jucatorului_2;
            dealer_total = 0;
            bani_jucator_1 -= miza_jucatorului_1;
            system( "pause" );
            system( "cls" );
            start_joc(f);
        }

        if (totalul_jucatorului_1 > 21)//daca are peste 21, a pierdut
        {

            printf( "%s a pierdut!\n", J1.nume);
            bani_jucator_1 -= miza_jucatorului_1;
            dealer_total = 0;
            bani_jucator_2 += miza_jucatorului_2;
            system( "pause" );
            system( "cls" );
            start_joc(f);
        }

        if (totalul_jucatorului_2 > 21)
        {

            printf( "%s a pierdut!\n", J2.nume);
            bani_jucator_2 -= miza_jucatorului_2;
            dealer_total = 0;
            bani_jucator_1 += miza_jucatorului_1;
            system( "pause" );
            system( "cls" );
            start_joc(f);
        }

        if ( totalul_jucatorului_1 < 21 )//daca are 21, alege ce sa faca
        {
            printf( "Randul lui %s\n", J1.nume );
            printf( "Alegeti H pentru inca o carte, S pentru a sta sau P pentru split\n" );
            scanf( "%c", &alegere);
//testam sa introduca ceva valid, adica H,S sau P
            while( (alegere != 'H' ) && ( alegere != 'h' ) && ( alegere != 'S' ) && ( alegere != 's' ) && ( alegere != 'P' ) && ( alegere != 'p' ) ) // Daca a introdus altceva
            {
                printf( "\n" );
                scanf( "%c", &alegere);
            }
//daca a ales H, mai ia o carte
            if ( ( alegere == 'H' ) || ( alegere == 'h' ) )
            {
                int aux;
                aux = carte( totalul_jucatorului_1, f );
                totalul_jucatorului_1 += aux;
                char semn_carte_jucator_actual = fgetc(f);
                afiseaza_carte ( aux, semn_carte_jucator_actual);//ii afisam cartea
                printf( "Totalul lui %s este: %d \n", J1.nume, totalul_jucatorului_1 );//si cat are pana acum
            }

            if ( ( alegere == 'S' ) || ( alegere == 's' ) )//Daca alege sa stea, sta
                x = 1;//asa contorizam daca vrea sa stea

            if ( ( alegere == 'P' ) || ( alegere == 'p' ) )
            {
                totalul_jucatorului_1 /= 2;
            }

        }//termina randul jucatorului 1

        if ( totalul_jucatorului_2 < 21)
        {
            printf( "Randul lui %s\n", J2.nume );
            printf( "Alegeti H pentru inca o carte, S pentru a sta sau P pentru split\n" );
            scanf( "%c", &alegere);

            while((alegere != 'H') && ( alegere != 'h' ) && ( alegere != 'S' ) && ( alegere != 's' ) && ( alegere != 'P' ) && ( alegere != 'p' ) ) // Daca iar nu a bagat bine
            {
                printf( "\n" );
                scanf( "%c", &alegere );
            }

            if ( ( alegere == 'H' ) || ( alegere == 'h' ) )
            {
                int aux;
                aux = carte( totalul_jucatorului_2, f);
                totalul_jucatorului_2 += aux;
                char semn_carte_jucator_actual = fgetc(f);
                afiseaza_carte( aux, semn_carte_jucator_actual);
                printf( "Totalul lui %s este: %d \n", J2.nume, totalul_jucatorului_2 );
            }

            if ( ( alegere == 'P' ) || ( alegere == 'p' ) )
            {
                totalul_jucatorului_2 /= 2;
            }

        }//termina randul jucatorului 2

        if( dealer_total == 21 ) //Daca dealerul are 21, au pierdut jucatoii
        {

            printf( "\nDealerul a castigat!\n" );
            bani_jucator_1 -= miza_jucatorului_1;
            bani_jucator_2 -= miza_jucatorului_2;
            dealer_total = 0;
            system( "pause" );
            system( "cls" );
            start_joc( f );
        }

        if( dealer_total > 21 ) //Daca dealerul are peste 21, jucatorii au castigat
        {

            printf( "\nAmbii jucatori au castigat!\n" );

            bani_jucator_1 += miza_jucatorului_1;
            bani_jucator_2 += miza_jucatorului_2;
            system( "pause" );
            system( "cls" );
            dealer_total = 0;
            start_joc( f );
        }

        dealer( f, &dealer_total );
        printf( "\nDealerul are: %d", dealer_total );
        printf( "\n" );

        i++;
//daca ambii jucatori au ales sa stea iar sumele lor sunt egale cu ale dealerului, e remiza
        if ( ( totalul_jucatorului_1 == totalul_jucatorului_2 ) && ( x==1 ) && ( ( alegere=='S' ) || ( alegere == 's' ) ) && ( totalul_jucatorului_1 == dealer_total) )
        {
            printf( "Egalitate!\n" );
            system( "pause" );
            system( "cls" );
            start_joc( f );
        }

        if ( (x == 1 ) && (( alegere == 'S' ) || ( alegere == 's' ) ) )//daca au ales amandoi sa stea, e randul dealerului
            dealer(f, &dealer_total);

    }//termina while

}//termina functia

void dealer(FILE *f, int *dealer_total)
{
    int valoare_carte_dealer = 0, b = 0;


    if ( *dealer_total < 17 )//daca dealerul are sub 17, mai trage carti, altfel, nu
    {
        //tragem o carte(valoare+semn) din fisier
        fscanf( f, "%d", &valoare_carte_dealer );
        fgetc(f);

        if (valoare_carte_dealer <= 10)
            b = valoare_carte_dealer;

        if ( valoare_carte_dealer > 11)
            b = 10;

        if ( valoare_carte_dealer == 11)
        {

            if( *dealer_total <= 10 )//daca dealerul are sub 10, asarul valoareaza 11, alfel 1
            {
                b = 11;
            }

            else
            {
                b = 1;
            }
        }

        *dealer_total += b;
    }
}

void test_bani(int *bani_jucator_1, int *bani_jucator_2, FILE *f)

{

    if ( *bani_jucator_1 <= 0 )
    {
        printf("Jucatorul %s nu mai are bani!\n",J1.nume);
        continuare( f, bani_jucator_1, bani_jucator_2 );
    }

    if ( *bani_jucator_2 <= 0 )
    {
        printf("Jucatorul %s nu mai are bani!\n",J2.nume);
        continuare( f, bani_jucator_1, bani_jucator_2 );
    }

}

int mizeaza(int bani)
{
    int miza = 0;
    static int numar_jucator = 1;
    printf( "Miza jucatorului %d\n", numar_jucator);
    scanf( "%d", &miza);

    while ( (miza > bani ) || ( miza <=0 ) )//daca se crede prea bogat sau prea sarac
    {
        printf( "Nu puteti miza mai multi bani decat aveti sau valori <= 0!\n" );
        printf( "Cat doriti sa mizati?\n" );
        scanf( "%d", &miza);
    }
    numar_jucator++;
    if (numar_jucator > 2)
        numar_jucator = 1;

    return miza;
}
//daca in vreun fel se termina jocul, intreaba daca vor sa joace iar
void continuare(FILE *f, int *bani_jucator_1, int *bani_jucator_2)
{
    char alegere;
    printf( "Doriti sa jucati din nou? \n" );
    printf( "Y-DA, N-NU\n" );
    scanf( "%c", &alegere);

    while( ( alegere != 'Y' ) && ( alegere != 'y' ) && ( alegere != 'N' ) && ( alegere != 'n' ) )
    {
        printf( "Y-DA, N-NU\n" );
        scanf( "%c", &alegere);
    }

    if ( ( alegere == 'Y' ) || ( alegere == 'y' ) )
    {
        system( "cls" );
        *bani_jucator_1 = 500;
        *bani_jucator_2 = 500;
        intrebare( f );
    }

    if ( ( alegere == 'N' ) || ( alegere == 'n' ) )
    {
        printf( "Poata alta data. O zi buna!\n" );
        system( "pause" );
        exit(0);
    }

}//termina functia

void generare_maini( FILE *f )
{
  //  struct carte c[NUMAR_MAINI];
    struct carte *c = (struct carte*)malloc(NUMAR_MAINI * sizeof(struct carte));
    int i = 0;
    char semne_carti[] = "CDHS";

    while( i != NUMAR_MAINI )//genereaza 1000 de carti in fisier
    {
        c[i].valoare = ( rand() % 13 ) + 2;//valori de la 2 la 14
        c[i].culoare = semne_carti [ rand() % (sizeof(semne_carti) - 1) ];//sizeof(semne_carti)=5, deci rand merge de la 1 la 4

        fprintf ( f, "%d%c", c[i].valoare, c[i].culoare );
        fprintf( f, "\n" );
        i++;
    }
    free(c);

}


