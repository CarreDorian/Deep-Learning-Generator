#include "lib.h"

char *cut(char **str, int *taille_mot, unsigned int *prio)
{
    int i;
    static unsigned stockprio = 0;
    prio -= stockprio;
    stockprio = 0;
    for (i = 0; (*str)[i] != '\0'; i++) {
        switch ((*str)[i]) {
            case ' ':
                while ((*str)[--i] == ' ');
                char *new_str = malloc((i + 1) * sizeof(char));
                for (int k = 0; k <= i; k++) {
                    new_str[k] = (*str)[k];
                }
                *taille_mot = i;
                for (i++; (*str)[i] == ' '; i++);
                (*str) = &(*str)[i];
                return (new_str);
            case '(':
                (*prio)++;
                printf("prio : %u", *prio);
                break;
            case ')':
                stockprio++;
        }
    }
    if ((*str)[0] == '\0'){
        return (NULL);
    }
    while ((*str)[--i] == ' ');
    char *new_str = malloc((i + 1) * sizeof(char));
    for (int k = 0; k <= i; k++) {
        new_str[k] = (*str)[k];
    }
    *taille_mot = i;
    (*str) = "";
    return (new_str);
}

int main () {
    // On récupère le calcul de l'utilisateur et on sépare les éléments grâce aux espaces 
    int taille_mot = 0;
    unsigned int prio = 0;
    char *str;
    char *mot;
    element_t *first = NULL;
    element_t *new;
    element_t *mots_a_parser;
    // printf("votre entrez > ");
    // gets(str);
    // printf("\n");
    str = "5 - 0.5 - 15 + (2 * (6 + 57) / (89 + 25)) * -15";
    printf("\n%s\n\n", str);
    if (str[0] == ' ') {
        while (str[++taille_mot] == ' ');
        str = &str[taille_mot];
    }
    mot = cut(&str, &taille_mot, &prio);
    if (mot != NULL) {
        new = malloc(sizeof(*mots_a_parser));
        new->mot = mot;
        new->taille = taille_mot;
        new->nbr = str_to_int(mot);
        // printf("mot : %s ; nbr : %f\n\n", next->mot, next->nbr);
        mots_a_parser = new;
        first = new;
        mot = cut(&str, &taille_mot, &prio);
        while (mot != NULL) {
            new = malloc(sizeof(*mots_a_parser));
            new->mot = mot;
            new->taille = taille_mot;
            new->nbr = str_to_int(mot);
            // printf("mot : %s ; nbr : %f\n\n", next->mot, next->nbr);
            mots_a_parser->next = new;
            mots_a_parser = new;
            mot = cut(&str, &taille_mot, &prio);
        }
    }

    printf("");
    long double result = parcing(first->next, first->nbr, 1);
    printf("le résultat est : %Lf\n", result);

    while (first != NULL) {
        // printf("\n\nvotre mot est \"%s\" et possède %d carractères. sa valeur est de %f.\n", mots_a_parser->mot, mots_a_parser->taille + 1, mots_a_parser->nbr);
        new = first;
        first = first->next;
        free(new);
    }
    return (0);
}
