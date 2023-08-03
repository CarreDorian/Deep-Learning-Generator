#include "../includes/includes.h"
// #include <ctype.h>

//////////////////////////// GLOBAL DEFINITION ////////////////////////////

vector <int> input;
vector<int> model;

int train = 0;

bool delate = 0;

char *charge = "default";
char *save = "default";


/////////////////////////////////// END ///////////////////////////////////

// ALERTE : change the word1 value
bool is_word_equals(char *&word1, char *word2) {
    if (strlen(word1) < strlen(word2))
        return false;

    for (int i = 0; i < strlen(word1); i++) {
        if (word1[i] != word2[i]) {
            if (word1[i] != ':') {
                return false;
            }

            word1 = &(word1[i+1]);
            return true;
        }
    }

    return true;
}

void get_before_points(char *&arg, char *&word) {
    for (int avencement = 0; avencement < strlen(arg); avencement++) { 

        if (arg[avencement] == ':') {

            word = arg;
            word[avencement] = '\0';
            arg = &(arg[avencement + 1]);    
            return;
        }
    }

    word = arg;
    arg = "";
    return;
}

// ALERTE : get the number into the "number" var
bool get_number(char *&arg, int &number) {
    number = 0;
    bool is_neg = 0;
    int avencement = -1; 

    if (arg[0] == '-') {
        avencement++;
        is_neg = 1;
    }

    while (++avencement < strlen(arg)) { 
        if (arg[avencement] == ':') {
            arg = &(arg[avencement+1]);
            return is_neg ? number - 1 : number;
        }

        int nbr = static_cast<int>(arg[avencement]) - 48;
        if (nbr < 0 && nbr > 9) {
            return -1;
        }

        number *= 10;
        number += nbr;
    }

    return is_neg ? number - 1 : number;
}

void detect_letter_option(char *arg) {
    
    int nbr;
    char *letters;
    get_before_points(arg, letters);

    for (int i = 0; i < strlen(letters); i++) {
        switch (letters[i]) {
        case 'c':
            charge = arg;
            break;

        case 't':
            if (!get_number(arg, nbr))
                break;

            train = nbr;
            break;

        case 'e':
            while (get_number(arg, nbr)) {
                input.push_back(nbr);
            }
            break;
        
        case 'd':
            delate = 1;
            break;

        case 's':
            save = arg;
            break;
        }
    }
}

void detect_word_option(char *arg) {

    if (is_word_equals(arg, "charge")) {
        charge = arg;

    } else if (is_word_equals(arg, "train")) {
        int nbr;
        if (!get_number(arg, nbr))
            return;
        train = nbr;

    } else if (is_word_equals(arg, "execute")) {
        int nbr;
        while (get_number(arg, nbr)) {
            input.push_back(nbr);
        }

    } else if (is_word_equals(arg, "delate")) {
        delate = 1;

    } else if (is_word_equals(arg, "save")) {
        save = arg;
    }
}

void detect_couches(char *arg) {
    int nbr_couche;
    bool is_nbr = get_number(arg, nbr_couche);
    
    if (is_nbr) {
        int nbr_neurones;
        is_nbr = get_number(arg, nbr_neurones);

        if (!is_nbr)
            return;
            
        for (int i = 0; i < nbr_couche; i++) {
            model.push_back(nbr_neurones);
        }
        return;
    }

    return;
}

// void toLowerCase(char *str) {
//     while (*str) {
//         *str = tolower(*str);
//         str++;
//     }
// }

int mot_clef(char *arg) {
    if (strlen(arg) >= 2 && arg[0] == '-') {
        if (strlen(arg) >= 3 && arg[1] == '-') {
            detect_word_option(&arg[2]);

        } else {
            detect_letter_option(&arg[1]);
        }
        return -1;
    }

    return 0;
}

int main(int argc, char **argv) {

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        
        switch (mot_clef(arg)) {
        case -1:
            break;
        default:
            detect_couches(arg);
        }
    }

    cout << "doit charger " << charge << "\nsauvegarder sous : " << save << "\ntrain " << train << "x times\ndoit-on ne pas auvegarder ? " << (delate ? "oui" : "non") << endl;

    vector <vector <int> > vec;
    vec.push_back(model);
    vec.push_back(input);
    for (auto v : vec) {
        vector <vector <int> > count;
        int av = -1;

        for (auto n : v) {
            if (av == -1) {
                av++;
                vector <int> j;
                j.push_back(n);
                j.push_back(1);
                count.push_back(j);
                continue;
            }

            if (count[av][0] == n) {
                count[av][1]++;
            }
            else {
                av++;
                vector <int> j;
                j.push_back(n);
                j.push_back(1);
                count.push_back(j);
                continue;
            }
        }

        cout << endl << "\n[\n";
        for (auto nbr : count) {
            cout << "\t" << nbr[1] << ":" << nbr[0] << ";\n";
        }
        cout << "]" << endl;
    }
    
    return 0;
}