#include "../includes/neurones.h"

double nbrAleatoire() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<double> distribution(0.0001f, 10000.0f);

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
        vector< vector<double> > couche;
        
        for (int i = 0; i < largeur; i++) {
            vector<double> neurone;
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
        vector< vector<double> > couche;
        
        for (int i = 0; i < largeur; i++) {
            vector<double> neurone;
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
    
    for (vector< vector<double> > coucheNeurones : reseau) {
        cout << "W" << count++;
        for (vector<double> couche : coucheNeurones) {
            cout << "\t";
            string str = "";
            for (double neurone : couche) {
                str += to_string(neurone) + ";";
            }
            str.erase(str.size() - 1); 
            cout << str << endl;
        }
    }
    cout << endl;
}

vector< vector< vector<double> > > Neurone::getModel() {
    return reseau;
}

void Neurone::chargeModel(vector< vector< vector<double> > > newReseau) {
    reseau = newReseau;
}

void Neurone::chargeModel() {
    reseau = read();
}

void Neurone::saveModel() {
    write(reseau);
}

double Neurone::sigmoide(double x) {
    if (x > 709.0)
        return 1.0;
    else if (x < -709.0) 
        return 0.0;
    else
        return 1.0 / (1.0 + exp(-x));
}

double Neurone::sigmoid_derivee(double x) {
    double sigmoid = sigmoid(x);
    return sigmoid * (1.0 - sigmoid);
}

double Neurone::calculForward(vector<double> neurone, vector<double> entree) {
    double calcul = 0;

    for (int index = 0; index < neurone.size(); index++) {
        calcul += neurone[index] * entree[index];
    }

    return sigmoide(calcul);
}

vector<double> Neurone::forward(vector<double> entree) {
    if (entree.size() != reseau[0][0].size()) {
        cout << "ERROR : Bad forward input. take " << reseau[0].size() << ", get " << entree.size() << "." << endl;
        return vector<double>();
    }
    resultCouche.clear();
    resultCouche.push_back(entree);
    int avancement = 0;

    for (vector< vector<double> > couche : reseau) {
        resultCouche.push_back(vector<double> ());
        for (vector<double> neurone : couche) {
            resultCouche[avancement].push_back(calculForward(neurone, entree));
        }
        entree = resultCouche[avancement];
    }

    return entree;
}

void Neurone::backward(vector<double> sortieAttendu) {

    for (int avancement = reseau.size() - 1, indexResult = resultCouche.size() - 1; avancement >= 0; avancement--) {
        vector<double> erreur;
        for (int index = 0; index < resultCouche[indexResult].size(); index++) {
            erreur.push_back(sortieAttendu[index] - resultCouche[indexResult][index]);
        }

        vector<double> erreurDelta;
        for (int index = 0; index < erreur.size(); index++) {
            erreurDelta.push_back(erreur[index] - sigmoid_derivee(resultCouche[indexResult][index]));
        }

        sortieAttendu = erreurDelta;

        for (int index = 0; index < reseau[avancement]; index++) {
            reseau[avancement][index] += resultCouche[--indexResult][index] * erreurDelta[index];
        }
    }
}