#include "../includes/neurones.h"

float nbrAleatoire() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<float> distribution(0.0001f, 10000.0f);

    return distribution(generator);
}

Neurone::Neurone(vector<int> model) {
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