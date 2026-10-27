
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person* position;

typedef struct _person
{
    char name[50];
    char lname[50];
    int year;
    position next;
} person;

int insertafter(position p, position newp);
int insertbegin(char* ime, char* prezime, int godina, position head);
int insertend(char* ime, char* prezime, int godina, position p);
int printlist(position p);
position findlastname(char* prezime, position p);
int deleteperson(char* prezime, position p);

int addafter(char* trazeno, char* ime, char* prezime, int godina, position head);
int addbefore(char* trazeno, char* ime, char* prezime, int godina, position head);
int sortlist(position head);
int writelist(char* datoteka, position head);
int readlist(char* datoteka, position head);

int insertafter(position p, position newp)
{
    newp->next = p->next;
    p->next = newp;
    return 0;
}

int insertbegin(char* ime, char* prezime, int godina, position head)
{
    position newperson = malloc(sizeof(person));

    if (newperson == NULL)
        return -1;

    strcpy(newperson->name, ime);
    strcpy(newperson->lname, prezime);
    newperson->year = godina;

    insertafter(head, newperson);

    return 0;
}

int insertend(char* ime, char* prezime, int godina, position p)
{
    position newperson = malloc(sizeof(person));

    if (newperson == NULL)
        return -1;

    strcpy(newperson->name, ime);
    strcpy(newperson->lname, prezime);
    newperson->year = godina;
    newperson->next = NULL;

    while (p->next != NULL)
        p = p->next;

    insertafter(p, newperson);

    return 0;
}

int printlist(position p)
{
    p = p->next;

    while (p != NULL)
    {
        printf("%s %s %d\n",
               p->name, p->lname, p->year);
        p = p->next;
    }

    return 0;
}

position findlastname(char* prezime, position p)
{
    p = p->next;

    while (p != NULL)
    {
        if (strcmp(p->lname, prezime) == 0)
            return p;

        p = p->next;
    }

    return NULL;
}

int deleteperson(char* prezime, position p)
{
    position prev = p;
    position curr = p->next;

    while (curr != NULL &&
           strcmp(curr->lname, prezime) != 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return -1;

    prev->next = curr->next;
    free(curr);

    return 0;
}

int addafter(char* trazeno, char* ime, char* prezime, int godina, position head)
{
    position p = findlastname(trazeno, head);
    if (p == NULL)
        return -1;

    position newperson = malloc(sizeof(person));

    if (newperson == NULL)
        return -1;

    strcpy(newperson->name, ime);
    strcpy(newperson->lname, prezime);
    newperson->year = godina;

    insertafter(p, newperson);

    return 0;
}

int addbefore(char* trazeno, char* ime, char* prezime, int godina, position head)
{
    position p = head;

    while (p->next != NULL && strcmp(p->next->lname, trazeno) != 0)
    {
        p = p->next;
    }

    if (p->next == NULL)
        return -1;

    position newperson = malloc(sizeof(person));

    if (newperson == NULL)
        return -1;

    strcpy(newperson->name, ime);
    strcpy(newperson->lname, prezime);
    newperson->year = godina;

    insertafter(p, newperson);

    return 0;
}

int sortlist(position head)
{
    position i, j;
    char ime[50], prezime[50];
    int godina;

    for (i = head->next; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->lname, j->lname) > 0)
            {
                strcpy(ime, i->name);
                strcpy(prezime, i->lname);
                godina = i->year;

                strcpy(i->name, j->name);
                strcpy(i->lname, j->lname);
                i->year = j->year;

                strcpy(j->name, ime);
                strcpy(j->lname, prezime);
                j->year = godina;
            }
        }
    }
    return 0;
}

int writelist(char* datoteka, position head)
{
    FILE* fp = fopen(datoteka, "w");

    if (fp == NULL)
        return -1;

    position p = head->next;

    while (p != NULL)
    {
        fprintf(fp, "%s %s %d\n", p->name, p->lname, p->year);
        p = p->next;
    }
    fclose(fp);
    return 0;
}

int readlist(char* datoteka, position head)
{
    FILE* fp = fopen(datoteka, "r");

    if (fp == NULL)
        return -1;

    char ime[50], prezime[50];
    int godina;

    while (fscanf(fp, "%49s %49s %d", ime, prezime, &godina) == 3)
    {
        if (insertend(ime, prezime, godina, head) != 0)
        {
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);

    return 0;
}

int main()
{
    char ime[50], prezime[50], trazeno[50];
    int godina;
    person head = { .next = NULL };
    position p = &head;
    position pronadena = NULL;

    insertbegin("Ana", "Anic", 2002, p);
    insertbegin("Ivan", "Ivic", 2000, p);
    insertend("Petra", "Peric", 2001, p);
    insertend("Marko", "Markic", 1999, p);
    
    printf("poc lista:\n");
    printlist(p);

    printf("unesi ime, prezime i god rodenja nove osobe: ");
    scanf("%49s %49s %d", ime, prezime, &godina);

    printf("iza kojeg prezimena zelis dodati osobu ");
    scanf("%49s", trazeno);

    if (addafter(trazeno, ime, prezime, godina, p) == 0)
        printlist(p);
    else
        printf("\ngreska\n");

    printf("unesi ime, prezime i god rodenja nove osobe: ");
    scanf("%49s %49s %d", ime, prezime, &godina);

    printf("ispred kojeg prezimena zelis dodati osobu ");
    scanf("%49s", trazeno);

    if (addbefore(trazeno, ime, prezime, godina, p) == 0)
        printlist(p);
    else
        printf("\ngreska\n");

    printf("\nkoje prezime zelis pretraziti ");
    scanf("%49s", trazeno);

    pronadena = findlastname(trazeno, p);
    if (pronadena != NULL)
        printf("%s %s %d\n", pronadena->name, pronadena->lname, pronadena->year);
    else
        printf("\ngreska\n");


    sortlist(p);

    printf("\nsortirana lista:\n");
    printlist(p);

    if (writelist("lista.txt", p) != 0)
        printf("\ngreska\n");


    while (p->next != NULL)
    {
        position temp = p->next;
        p->next = temp->next;
        free(temp);
    }

    if (readlist("osobe.txt", p) == 0)
        printf("\nlista iz datoteke:\n");
    else
        printf("\ngreska\n");

    printlist(p);

    while (p->next != NULL)
    {
        position temp = p->next;
        p->next = temp->next;
        free(temp);
    }
    return 0;
}
