#include "../includes/neurones.h"

float nbrAleatoire() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<float> distribution(0.0001f, 10000.0f);

    return distribution(generator);
}

Neurone::Neurone(vector<int> model) : File() {
    for (int largeur : model) {
        if (largeur < 1)
            cout << "ERROR : bad model ask." << endl;
        vector<float> couche;
        
        for (int i = 0; i < largeur; i++) {
            couche.push_back(nbrAleatoire());
        }
        reseau.push_back(couche);
    }
}

Neurone::Neurone(char *importReseau) : File(importReseau) {
    chargeModel();
}

Neurone::Neurone(vector<int> model, char *importReseau) : File(importReseau) {
    for (int largeur : model) {
        if (largeur < 1)
            cout << "ERROR : bad model ask." << endl;
        vector<float> couche;
        
        for (int i = 0; i < largeur; i++) {
            couche.push_back(nbrAleatoire());
        }
        reseau.push_back(couche);
    }
}

void Neurone::showModel() {
    int count = 0;

    for (auto largeur : reseau) {
        cout << "W" << ++count;
        for (float poid : largeur) {
            cout << '\t' << poid;
        }
        cout << endl;
    }
}

vector< vector<float> > Neurone::getModel() {
    return reseau;
}

void Neurone::chargeModel(vector< vector<float> > newReseau) {
    reseau = newReseau;
}

void Neurone::chargeModel() {
    reseau = read();
}

void Neurone::saveModel() {
    write(reseau);
}