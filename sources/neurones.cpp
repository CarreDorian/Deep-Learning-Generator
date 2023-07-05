#include "../includes/neurones.h"

float nbrAleatoire() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<float> distribution(0.0001f, 10000.0f);

    return distribution(generator);
}

Neurone::Neurone(vector<int> model) : File() {
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
        vector< vector<float> > couche;
        
        for (int i = 0; i < largeur; i++) {
            vector<float> neurone;
            for (int j = 0; j < entree; j++) {
                neurone.push_back(nbrAleatoire());
            }
            couche.push_back(neurone);
        }
        reseau.push_back(couche);
    }
}

Neurone::Neurone(char *importReseau) : File(importReseau) {
    chargeModel();
}

Neurone::Neurone(vector<int> model, char *importReseau) : File(importReseau) {
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
        vector< vector<float> > couche;
        
        for (int i = 0; i < largeur; i++) {
            vector<float> neurone;
            for (int j = 0; j < entree; j++) {
                neurone.push_back(nbrAleatoire());
            }
            couche.push_back(neurone);
        }
        reseau.push_back(couche);
    }
}

void Neurone::showModel() {
    int count = 1;
    
    for (vector< vector<float> > coucheNeurones : reseau) {
        cout << "W" << count++;
        for (vector<float> couche : coucheNeurones) {
            cout << "\t";
            string str = "";
            for (float neurone : couche) {
                str += to_string(neurone) + ";";
            }
            str.erase(str.size() - 1); 
            cout << str << endl;
        }
    }
    cout << endl;
}

vector< vector< vector<float> > > Neurone::getModel() {
    return reseau;
}

void Neurone::chargeModel(vector< vector< vector<float> > > newReseau) {
    reseau = newReseau;
}

void Neurone::chargeModel() {
    reseau = read();
}

void Neurone::saveModel() {
    write(reseau);
}

vector<float> Neurone::forward(vector<float> entree) {
    // if (entree.size() != reseau[0].size()) {
    //     cout << "ERROR : Bad forward input. take " << reseau[0].size() << ", get " << entree.size() << "." << endl;
    //     return vector<float>();
    // }
    // vector<float> resultCouche;

    // for (vector<float> poids : reseau) {
    //     for (float entreeNeurone : entree) {
    //         for (poid : poids) {
    //             entreeNeurone
    //         }
    //     }
    // }
    return vector<float>();
}

void Neurone::backward() {}