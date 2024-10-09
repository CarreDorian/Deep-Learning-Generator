#include "../includes/neurones.h"
#include "profile.cpp"

// void printTypeById(string name) {

//     if (std::strlen(name.c_str()) > 1) {
//         if(name[0] == 'P' && name[1] == 'c') {
//             cout << "char*" << endl;
//         } else {
//             cout << name << endl;
//         }
//         return;
//     }

//     switch (name[0]) {
//         case 'i':
//             cout << "int" << endl;
//             break;
//         case 'c':
//             cout << "char" << endl;
//             break;
//         case 'd':
//             cout << "double" << endl;
//             break;
//         case 'f':
//             cout << "float" << endl;
//             break;
//         case 'l':
//             cout << "long" << endl;
//             break;
//         case 'j':
//             cout << "unsigned int" << endl;
//             break;
//         case 's':
//             cout << "short" << endl;
//             break;
//         case 't':
//             cout << "unsigned short" << endl;
//             break;
//         case 'x':
//             cout << "long long" << endl;
//             break;
//         case 'y':
//             cout << "unsigned long long" << endl;
//             break;
//         case 'b':
//             cout << "bool" << endl;
//             break;
//         default:
//             cout << name << endl;
//     }
// }

// template<typename T>
// void printType() {
//     string name = typeid(T).name();
//     printTypeById(name);
// }


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



int nbrAleatoire(int nbr_max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 Generator(seed);
    std::uniform_int_distribution<int> distribution(0, nbr_max - 1);

    return distribution(Generator);
}

int main() {
    vector< vector<double> > toPredictData;
    vector< vector<double> > outDataWait;
    auto brutData = setupDataset(toPredictData, outDataWait);

    vector<int> test(30,10);
    test.insert(test.begin(), 3);
    test.push_back(5);
    Neurone Einstein(test);
    Einstein.showModel();

    Einstein.entrainement(toPredictData, outDataWait);
    cout << endl;
    // Einstein.showModel();

    int random_nbr = nbrAleatoire(brutData.size());

    cout << "try the model. He predict : " << endl;
    auto prediction = Einstein.prediction(toPredictData[random_nbr]);

    Profile user(brutData[random_nbr].first, prediction[0], prediction[1], prediction[2], prediction[3], prediction[4], brutData[random_nbr].second[5], brutData[random_nbr].second[6], brutData[random_nbr].second[7]);
    user.affich();
    cout << endl << "voici les véritables données :" << endl;
    Profile realUser(brutData[random_nbr].first, brutData[random_nbr].second[0], brutData[random_nbr].second[1], brutData[random_nbr].second[2], brutData[random_nbr].second[3], brutData[random_nbr].second[4], brutData[random_nbr].second[5], brutData[random_nbr].second[6], brutData[random_nbr].second[7]);
    realUser.affich();
    
    return 0;
}