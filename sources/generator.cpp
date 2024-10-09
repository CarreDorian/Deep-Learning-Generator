#include "../includes/neurones.h"

double nbrAleatoire() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 Generator(seed);
    std::uniform_real_distribution<double> distribution(0.0001f, 10000.0f);

    return distribution(Generator);
}

Generator::Generator() : File() {}

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

Generator::Generator(char *nameImportReseau) : File(nameImportReseau) {
    chargeModel();
}

Generator::Generator(vector<int> model, char *nameImportReseau) : File(nameImportReseau) {
    if (model.size() < 2) {
        cout << "ERROR : bad model ask. Too fiew level." << endl;
        return;
    }
    vector< vector< vector<double> > > newReseau;
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
        newReseau.push_back(couche);
    }
    chargeModel(newReseau);
    chargeModel();
}

Generator::~Generator() {}

void Generator::modelFusion(char *nameImportReseau) {
    char *name = fileName;
    fileName = nameImportReseau;
    chargeModel();
    fileName = name;
}

void Generator::showModel() {
    int count = 1;
    if (reseau.size() == 0) {
        cout << "Empty" << endl;
        return;
    }
    
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

void Generator::addToBeginReseau(vector<int> model) {
    
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
        reseau.insert(reseau.begin(), couche);
    }
}

void Generator::addToEndReseau(vector<int> model) {
    
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

void Generator::chargeModel(vector< vector< vector<double> > > newReseau) {
    if (reseau.size() > 0 && newReseau.size() > 0) {
        vector< vector<double> > couche = reseau.back();
        vector< vector<double> > new_couche = newReseau[0];

        if (couche.size() < 1) {
            cout << "ERROR : can't add this two modules. The second caused don't got neurones" << endl;
            return;
        }
        if (new_couche[0].size() != couche.size()) {
            cout << "ERROR : can't add this two modules. They're not corresponding" << endl;
            return;
        }
    }
    reseau.insert(reseau.end(), newReseau.begin(), newReseau.end());
}

void Generator::chargeModel() {
    vector< vector< vector<double> > > model = read();

    if (reseau.size() > 0 && model.size() > 0) {
        vector< vector<double> > couche = reseau.back();
        vector< vector<double> > new_couche = model[0];

        if (couche.size() < 1) {
            cout << "ERROR : can't add this two modules. The second caused don't got neurones" << endl;
            return;
        }
        if (new_couche[0].size() != couche.size()) {
            cout << "ERROR : can't add this two modules. They're not corresponding" << endl;
            return;
        }
    }

    reseau.insert(reseau.end(), model.begin(), model.end());
}

void Generator::saveModel() {
    write(reseau);
}