
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ime[20];
    char prezime[20];
    int bodovi;
} Student;

int br(FILE *f) {
    char red[100];
    int broj=0;

    while (fgets(red, 100, f)!=NULL) {
        broj++;
    }

    rewind(f);
    return broj;
}

void ucitaj(FILE *f, Student studenti[], int broj) {
    int i;

    for (i = 0; i < broj; i++) {
        fscanf(f, "%19s %19s %d",
               studenti[i].ime,
               studenti[i].prezime,
               &studenti[i].bodovi);
    }
}

void ispisi(Student studenti[], int broj, int maxBodova) {
    int i;

    for (i = 0; i < broj; i++) {
        printf("%s %s %d %.2f%%\n",
               studenti[i].ime,
               studenti[i].prezime,
               studenti[i].bodovi,
               (float)studenti[i].bodovi / maxBodova * 100);
    }
}

int main(void) {
    FILE *f;
    Student *studenti;
    int broj, maxb;

    f=fopen("studenti.txt", "r");

    if (f==NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    broj=br(f);

    studenti=malloc(broj*sizeof(Student));

    if (studenti==NULL && broj>0) {
        fclose(f);
        return 1;
    }

    ucitaj(f, studenti, broj);

    printf("Unesi maksimalni broj bodova:\n");
    scanf(" %d", &maxb);

    ispisi(studenti, broj, maxb);

    free(studenti);
    fclose(f);

    return 0;
}
