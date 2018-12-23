#include <stdio.h>
#include <stdlib.h>
#include "functii.h"

int main()
{
    srand(time(0));//punem un seed pentru functia random
    FILE  *f = fopen(nume_fisier, "w+");//deschidem fisierul in care scriem si din care citim

    if (f == NULL)//testam daca putem deschide fisierul
    {
        printf("Nu pot deschide fisierul!");
        exit(0);
    }

    generare_maini(f);
    fseek(f, 0, SEEK_SET);//mutam cursorul la inceputul fisierului
    mesaj();
    citire_date();
    intrebare(f);
    fclose(f);
    return 0;
}
