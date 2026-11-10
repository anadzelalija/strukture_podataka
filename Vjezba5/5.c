#include <stdio.h>
#include <stdlib.h>

typedef struct Stog* Position;

typedef struct Stog {
    int broj;
    Position next;
} stog;

int Push(int, Position);
int Pop(int*, Position);
int Racunaj(char, Position);

int Push(int broj, Position P) {
    Position novi = (Position)malloc(sizeof(stog));

    if (novi == NULL) {
        return -1;
    }
    novi->broj = broj;
    novi->next = P->next;
    P->next = novi;

    return 0;
}

int Pop(int* broj, Position P) {
    Position pomocni = P->next;

    if (pomocni == NULL)
        return -1;

    *broj = pomocni->broj;
    P->next = pomocni->next;
    free(pomocni);

    return 0;
}

int Racunaj(char operacija, Position P) {
    int prvi, drugi, rezultat;

    if (Pop(&prvi, P) != 0)
        return -1;

    if (Pop(&drugi, P) != 0)
        return -1;

    switch (operacija) {
    case '+':
        rezultat = drugi + prvi;
        break;

    case '-':
        rezultat = drugi - prvi;
        break;

    case '*':
        rezultat = drugi * prvi;
        break;

    case '/':
        if (prvi == 0)
            return -1;

        rezultat = drugi / prvi;
        break;

    default:
        return -1;
    }

    return Push(rezultat, P);
}

int main() {
    stog head={0, NULL};
    char izraz[20];
    int broj, prvi, drugi;

    FILE* fp=fopen("a.txt", "r");

    if (fp==NULL) {
        return -1;
    }

    while (fscanf(fp, "%19s", izraz)==1) {

        if (sscanf(izraz, "%d", &broj)==1) {
            Push(broj, &head);
        }
        else {
            if (Racunaj(izraz[0], &head)!=0) {
                fclose(fp);

                while (Pop(&prvi, &head)==0);
                return -1;
            }
        }
    }

    fclose(fp);

    if (Pop(&drugi, &head)!=0 || head.next!=NULL) {
        printf("greska\n");

        while (Pop(&prvi, &head)==0);
        return -1;
    }

    printf("rezultat: %d\n", drugi);

    return 0;
}