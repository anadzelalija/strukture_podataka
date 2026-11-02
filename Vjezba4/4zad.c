#include <stdio.h>
#include <stdlib.h>

typedef struct Polinom* position;

typedef struct Polinom
{
    int koef;
    int eksp;
    position next;
} polinom;

int ucitaj(position, position);
int umetni(int, int, position);
int ispisi(position);
int zbroji(position, position, position);
int mnozi(position, position, position);

int ucitaj(position p1, position p2)
{
    FILE* fp;
    position trenutni;
    char redak[1000];
    int i, koef, eksp, pozicija, procitano;

    fp = fopen("polinom.txt", "r");

    if (fp == NULL)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        if (i == 0)
            trenutni = p1;
        else
            trenutni = p2;

        if (fgets(redak, sizeof(redak), fp) == NULL)
        {
            fclose(fp);
            return -1;
        }
        pozicija = 0;

        while (sscanf(redak + pozicija, "%d %d%n", &koef, &eksp, &procitano) == 2)
        {
            if (umetni(koef, eksp, trenutni) != 0)
            {
                fclose(fp);
                return -1;
            }
            pozicija += procitano;
        }
    }
    fclose(fp);
    return 0;
}

int umetni(int koef, int eksp, position glava)
{
    position prethodni = glava;
    position novi;

    while (prethodni->next != NULL && prethodni->next->eksp > eksp)
        prethodni = prethodni->next;

    if (prethodni->next != NULL && prethodni->next->eksp == eksp)
    {
        prethodni->next->koef += koef;

        if (prethodni->next->koef == 0)
        {
            novi = prethodni->next;
            prethodni->next = novi->next;
            free(novi);
        }

        return 0;
    }

    novi = malloc(sizeof(polinom));

    if (novi == NULL)
        return -1;

    novi->koef = koef;
    novi->eksp = eksp;

    novi->next = prethodni->next;
    prethodni->next = novi;

    return 0;
}

int ispisi(position p)
{
    if (p == NULL)
    {
        printf("0\n");
        return 0;
    }

    while (p != NULL)
    {
        if (p != NULL && p->koef > 0)
            printf("+");

        printf("%d", p->koef);

        if (p->eksp > 0)
            printf("x");

        if (p->eksp > 1)
            printf("^%d", p->eksp);

        p = p->next;
    }

    printf("\n");
    return 0;
}

int zbroji(position p1, position p2, position rezultat)
{
    position p;

    p = p1->next;

    while (p != NULL)
    {
        if (umetni(p->koef, p->eksp, rezultat) != 0)
            return -1;

        p = p->next;
    }

    p = p2->next;

    while (p != NULL)
    {
        if (umetni(p->koef, p->eksp, rezultat) != 0)
            return -1;

        p = p->next;
    }

    return 0;
}

int mnozi(position p1, position p2, position rezultat)
{
    position p, q;

    p = p1->next;

    while (p != NULL)
    {
        q = p2->next;

        while (q != NULL)
        {
            if (umetni(p->koef * q->koef,
                       p->eksp + q->eksp, rezultat) != 0)
                return -1;

            q = q->next;
        }

        p = p->next;
    }

    return 0;
}


int main()
{
    polinom p1 = { 0, 0, NULL };
    polinom p2 = { 0, 0, NULL };
    polinom zbroj = { 0, 0, NULL };
    polinom umnozak = { 0, 0, NULL };

    if (ucitaj(&p1, &p2) != 0)
        return 1;

    printf("prvi polinom: ");
    ispisi(p1.next);

    printf("drugi polinom: ");
    ispisi(p2.next);

    zbroji(&p1, &p2, &zbroj);
    printf("zbroj: ");
    ispisi(zbroj.next);

    mnozi(&p1, &p2, &umnozak);
    printf("umnozak: ");
    ispisi(umnozak.next);

    position temp;

    while (p1.next != NULL)
    {
        temp = p1.next;
        p1.next = temp->next;
        free(temp);
    }

    while (p2.next != NULL)
    {
        temp = p2.next;
        p2.next = temp->next;
        free(temp);
    }

    while (zbroj.next != NULL)
    {
        temp = zbroj.next;
        zbroj.next = temp->next;
        free(temp);
    }

    while (umnozak.next != NULL)
    {
        temp = umnozak.next;
        umnozak.next = temp->next;
        free(temp);
    }
    return 0;
}