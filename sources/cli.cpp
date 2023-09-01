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

vector< pair< string, vector<int> > > setupDataset(vector< vector<double> > &toPredictData, vector< vector<double> > &outDataWait) {
    toPredictData.clear();
    outDataWait.clear();
    vector< vector<string> > names;
    if (1) { // ceci est pour cacher ces lignes interminables
        vector<string> noms;

        noms.push_back("puce");
        noms.push_back("Bernard");
        noms.push_back("Bernadette");
        noms.push_back("Jack");
        noms.push_back("Tulipe");
        noms.push_back("Jean");
        noms.push_back("Julie");
        noms.push_back("Susane");
        names.push_back(noms);
        noms.clear();

        noms.push_back("fleure");
        noms.push_back("jaqueline");
        noms.push_back("Jacob");
        noms.push_back("paul");
        noms.push_back("Tulipette");
        noms.push_back("Sogna");
        noms.push_back("Morgane");
        names.push_back(noms);
        noms.clear();

        noms.push_back("radiateur");
        noms.push_back("Phillipe");
        noms.push_back("Paul");
        noms.push_back("suson");
        noms.push_back("Antoinette");
        noms.push_back("Alice");
        noms.push_back("Martine");
        noms.push_back("Franck");
        noms.push_back("Lionnel");
        noms.push_back("Susette");
        noms.push_back("Josianne");
        names.push_back(noms);
        noms.clear();

        noms.push_back("carbonne");
        noms.push_back("Francois");
        noms.push_back("Claudine");
        noms.push_back("Sebastien");
        noms.push_back("lucette");
        noms.push_back("Laurent");
        noms.push_back("Matilde");
        noms.push_back("Pascale");
        noms.push_back("Morgane");
        names.push_back(noms);
        noms.clear();

        noms.push_back("boulet");
        noms.push_back("Fabien");
        noms.push_back("Didier");
        names.push_back(noms);
        noms.clear();

        noms.push_back("sucette");
        noms.push_back("George");
        noms.push_back("Odile");
        noms.push_back("Celine");
        noms.push_back("Tulipe");
        noms.push_back("Jean");
        noms.push_back("Julie");
        noms.push_back("Susane");
        names.push_back(noms);
        noms.clear();

        noms.push_back("bristol");
        noms.push_back("Gaetan");
        noms.push_back("Yan");
        noms.push_back("Camille");
        names.push_back(noms);
        noms.clear();

        noms.push_back("bruler");
        noms.push_back("George");
        noms.push_back("Augustin");
        noms.push_back("Emilie");
        names.push_back(noms);
        noms.clear();
    }

    vector< pair< string, vector<int> > > data;

    ifstream dataset("dataset/Dataset.csv");
    int famille_index = 0, prenom_index = 1;
    string name = names[famille_index][0] + " " + names[famille_index][prenom_index++];
    pair< string, vector<int> > user = make_pair(name, vector<int>());
    string line;
    getline(dataset, line);

    while (getline(dataset, line)) {
        int dizaine = 0, nbr = 0;
        for (char carac : line) {
            if (dizaine == 0) {
                if (carac == ',')
                    dizaine++;
                continue;
            }

            switch (carac) {
                case ',':
                    user.second.push_back(nbr);
                    nbr = 0;
                    dizaine = 1;
                    break;

                default:
                    carac -= 48;
                    if (carac < 0 || carac > 9) {
                        cout << "ERROR : bad character in dataset" << endl;
                        return vector< pair< string, vector<int> > >();
                    }
                    nbr += carac * dizaine;
                    dizaine *= 10;
            }
        }
        user.second.push_back(nbr);
        nbr = 0;
        dizaine = 0;
        if (user.second.size() > 1) {
            data.push_back(user);
        }
        user = make_pair(name, vector<int>());
        if (names[famille_index].size() == prenom_index) {
            prenom_index = 1;
            if (++famille_index == names.size())
                famille_index = 0;
        }
        name = names[famille_index][0] + " " + names[famille_index][prenom_index++];
    }
    
    dataset.close();

    for (auto element : data) {
        int i = 0;
        vector<double> vec;
        while (i < 5) {
            vec.push_back(static_cast<double>(element.second[i++]));
        }
        outDataWait.push_back(vec);

        vec.clear();
        while (i < 8) {
            vec.push_back(static_cast<double>(element.second[i++]));
        }
        toPredictData.push_back(vec);
    }  

    return data;
}

int main(int argc, char **argv) {
    ///////// Ces trois lignes sont a décommenter afin de tester sur mon dataset de test. /////////
    // vector< vector<double> > toPredictData;
    // vector< vector<double> > outDataWait;
    // auto brutData = setupDataset(toPredictData, outDataWait);

    Neurone Einstein();

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        
        switch (mot_clef(arg)) {
        case -1:
            break;
        default:
            detect_couches(arg);
        }
    }

    if (model.size() > 1) {
        Neurone ia(model, save);
        Einstein = ia;
    } else if (charge != "") {
        Neurone ia(model, save);
        Einstein = ia;
    } else {
        cout << "no IA generated. Close. Goodbye !" << endl;
        return 0;
    }


    
    return 0;
}