#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person* position;

typedef struct _person
{   char name[50];
    char lname[50];
    int year;
    position next;
} person;

int insertafter(position p, position newp)
{newp->next = p->next;
    p->next = newp;
    return 0;
}

int insertbegin(char* ime, char* prezime, int godina, position head)
{
    position newperson = NULL;
    newperson = (position)malloc(sizeof(person));

    if (newperson == NULL)
        return -1;

    newperson->year = godina;
    strcpy(newperson->name, ime);
    strcpy(newperson->lname, prezime);

    insertafter(head, newperson);
    return 0;
}

int printlist(position p)
{   p = p->next;
    if (p == NULL)
    {   printf("Lista je prazna.\n");
        return 0;
    }

    while (p != NULL)
    {   printf("%s %s %d\n", p->name, p->lname, p->year);
        p = p->next;
    }

    return 0;
}

int insertend(char* ime, char* prezime, int godina, position p)
{   position newperson = NULL;

    newperson = (position)malloc(sizeof(person));
    if (newperson == NULL)
        return -1;

    newperson->year = godina;
    strcpy(newperson->name, ime);
    strcpy(newperson->lname, prezime);
    newperson->next = NULL;

    while (p->next != NULL)
    {   p = p->next;
    }

    insertafter(p, newperson);
    return 0;
}

position findlastname(char* prezime, position p)
{
    for (p = p->next; p != NULL; p = p->next)
    {   if (strcmp(p->lname, prezime) == 0)
        return p;
    }
    return NULL;
}

int deleteperson(char* prezime, position p)
{
    position prev = p;
    position curr = p->next;

    while (curr != NULL && strcmp(curr->lname, prezime) != 0)
    {   prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return -1;

    prev->next = curr->next;
    free(curr);
    return 0;
}

int main()
{
    person head= {
        .name={0},
        .lname={0},
        .year=0,
        .next=NULL
    };

    position p=&head;
    position pronadena=NULL;

    char ime[50];
    char prezime[50];
    int godina;

    insertbegin("Ivan", "Ivic", 2000, p);
    insertbegin("Mate", "Matic", 2004, p);
    insertend("Marko", "Markic", 1999, p);
    insertend("Petra", "Peric", 2001, p);

    printf("Poc lista:\n");
    printlist(p);

    printf("Unesi ime, prezime i godinu rodenja: ");
    scanf(" %49s %49s %d", ime, prezime, &godina);

    if (insertbegin(ime, prezime, godina, p) == 0)
        printf("Osoba je dodana na pocetak liste\n");
    else
        printf("Greska\n");

    printf("Lista nakon dodavanja:\n");
    printlist(p);

    printf("Unesi ime, prezime i godinu rodenja: ");
    scanf(" %49s %49s %d", ime, prezime, &godina);
    
    if (insertend(ime, prezime, godina, p) == 0)
        printf("Osoba je dodana na kraj liste\n");
    else
        printf("Greska\n");

    printf("Lista nakon dodavanja:\n");
    printlist(p);


    printf("Unesi prezime osobe koju zelis pronaci: ");
    scanf(" %49s", prezime);

    pronadena=findlastname(prezime, p);

    if (pronadena!=NULL)
        printf("Pronadena osoba: %s %s %d\n",pronadena->name,pronadena->lname,pronadena->year);
    
    else
        printf("Osoba nije pronadena\n");
    
    printf("Lista nakon pretrazivanja:\n");
    printlist(p);

    printf("Unesi prezime osobe koju zelis obrisati: ");
    scanf(" %49s", prezime);

    if (deleteperson(prezime, p) == 0)
        printf("Osoba je obrisana.\n");
    else
        printf("Osoba nije pronadena.\n");

    printf("Lista nakon brisanja:\n");
    printlist(p);

    while (p->next != NULL)
    {   position temp=p->next;
        p->next=temp->next;
        free(temp);
    }
    return 0;
}