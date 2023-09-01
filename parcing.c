#include "lib.h"

long double str_to_int(char *str) {
    int signe = 1, i = 0;
    long double result = 0;
    if (str[i + 1] != '\0') {
        if (str[i] =='-') {
            i++;
            signe = -1;
        }
        while (str[i] == '(')
            i++;
    }
    while (str[i] != '\0'){
        // quand on détecte que l'on entre dans une partie décimale, il s'adapte
        
        if (str[i] < 48)
            break;
        else if (str[i] > 57)
            break;
        result *= 10;
        result += str[i] % 48;
        i++;
    }
    switch (str[i]) {
        case '.':
        case ',':
        while (str[++i] != '\0') {
            if (str[i] < 48){
                break;}
            else if (str[i] > 57){
                break;}
            result += (str[i] % 48) * 0.1;
            i++;
        }
    }
    return(result * signe);
}

long double parcing(element_t *mots_a_parser, long double result, int bool) {
    if (mots_a_parser->next == NULL)
        return(result);
    int ok = 1;
    element_t *next = mots_a_parser->next; 
    
    printf("{ %s\n", mots_a_parser->mot);
    if (mots_a_parser->next->next != NULL) {
        printf ("mots : %s ; prio : %d ; mot suiv : %s ; prio suiv : %d\n", mots_a_parser->mot, mots_a_parser->prio, next->mot,  next->prio);
        if (mots_a_parser->prio < next->prio) {
                printf("parentaise suivante proritaire !!! :\n");
            while (mots_a_parser->prio < next->next->prio) {
                next->nbr = parcing(next->next, next->nbr, 0);
                if (next->next->next->next == NULL) {
                    next = NULL;
                    break;
                }
                next = next->next->next;
                printf("next = %s\n", next->next->mot);
            }
        } else {
            switch (next->next->mot[0]) {
                case '*':
                case 'x':
                case '/':
                case '%':

                printf("calcul proritaire !!! :\n");
                    next->nbr = parcing(next->next, next->nbr, 0);
                    while (ok) {
                        if (next->next->next->next == NULL) {
                            next = NULL;
                            break;
                        }
                        next = next->next->next;
                        printf("next = %s\n", next->next->mot);
                        switch (next->next->mot[0]) {
                            case '-':
                            case '+':
                                ok = 0;
                        }
                    }
            }
        }
    }

    switch (mots_a_parser->mot[0]) {
        case '+':
            printf("%Lf + %Lf", result, mots_a_parser->next->nbr);
            result += mots_a_parser->next->nbr;
            printf(" = %Lf\n", result);
            break;
        case '-':
            printf("%Lf - %Lf", result, mots_a_parser->next->nbr);
            result -= mots_a_parser->next->nbr;
            printf(" = %Lf\n", result);
            break;
        case 'x':
        case '*':
            printf("%Lf * %Lf", result, mots_a_parser->next->nbr);
            result *= mots_a_parser->next->nbr;
            printf(" = %Lf\n", result);
            break;
        case '/':
            printf("%Lf / %Lf", result, mots_a_parser->next->nbr);
            result /= mots_a_parser->next->nbr;
            printf(" = %Lf\n", result);
            break;
        case '%':
            printf("%Lf + %Lf", result, mots_a_parser->next->nbr);
            result += mots_a_parser->next->nbr;
            printf(" = %Lf\n", result);
            break;
    }
    printf("bool : %d\n", bool);
    printf("%s }\n\n", mots_a_parser->mot);
    if (next && bool){
        printf("next = %s\n", next->next->mot);
        printf("result : %Lf\n",result);
        result = parcing(next->next, result, 1);}
    return (result);
}