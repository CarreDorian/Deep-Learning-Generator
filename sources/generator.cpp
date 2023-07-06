#include "../includes/neurones.h"

double nbrAleatoire() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 Generator(seed);
    std::uniform_real_distribution<double> distribution(0.0001f, 10000.0f);

    return distribution(Generator);
}

Generator::Generator(vector<int> model) : File() {
    if (model.size() < 2) {
        cout << "ERROR : bad model ask. Too fiew level." << endl;
        return;
    }
    for (int step = 0; step < model.size() - 1; step++) {
        int largeur = model[step + 1];
        int entree = model[step];
        if (largeur < 1) {
            cout << "ERROR : bad model ask. Too few neurons" << endl;
            return;
        }
        vector< vector<double> > couche;
        
        for (int i = 0; i < largeur; i++) {
            vector<double> Generator;
            for (int j = 0; j < entree; j++) {
                Generator.push_back(nbrAleatoire());
            }
            couche.push_back(Generator);
        }
        reseau.push_back(couche);
    }
}

Generator::Generator(char *importReseau) : File(importReseau) {
    chargeModel();
}

Generator::Generator(vector<int> model, char *importReseau) : File(importReseau) {
    if (model.size() < 2) {
        cout << "ERROR : bad model ask. Too fiew level." << endl;
        return;
    }
    for (int step = 0; step < model.size() - 1; step++) {
        int largeur = model[step + 1];
        int entree = model[step];
        if (largeur < 1) {
            cout << "ERROR : bad model ask. Too few neurons" << endl;
            return;
        }
        vector< vector<double> > couche;
        
        for (int i = 0; i < largeur; i++) {
            vector<double> Generator;
            for (int j = 0; j < entree; j++) {
                Generator.push_back(nbrAleatoire());
            }
            couche.push_back(Generator);
        }
        reseau.push_back(couche);
    }
}

void Generator::showModel() {
    int count = 1;
    
    for (vector< vector<double> > coucheNeurones : reseau) {
        cout << "W" << count++;
        for (vector<double> couche : coucheNeurones) {
            cout << "\t";
            string str = "";
            for (double generator : couche) {
                str += to_string(generator) + ";";
            }
            str.erase(str.size() - 1); 
            cout << str << endl;
        }
    }
    cout << endl;
}

vector< vector< vector<double> > > Generator::getModel() {
    return reseau;
}

void Generator::chargeModel(vector< vector< vector<double> > > newReseau) {
    reseau = newReseau;
}

void Generator::chargeModel() {
    reseau = read();
}

void Generator::saveModel() {
    write(reseau);
}