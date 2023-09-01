/*                                                                                                                                      
** ETNA PROJECT, 23/10/2020 by carre_d                                                                                                  
** [...]                                                                                                                                
** File description:                                                                                                                    
**      import                                                                                                                          
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_tbl
{
    char *mot;
    int taille;
    unsigned int prio;
    long double nbr;
    struct s_tbl *next;
} element_t;

// macros :




long double parcing(element_t *mots_a_parser, long double result, int bool);
long double str_to_int(char *str);

