#include "../includes/neurones.h"

string printTypeById(string name) {

    if (std::strlen(name.c_str()) > 1) {
        if(name[0] == 'P' && name[1] == 'c') {
            return "char*";
        }
        return "ERROR";
    }

    switch (name[0]) {
        case 'i':
            return "int";
        case 'c':
            return "char";
        case 'd':
            return "double";
        case 'f':
            return "float";
        case 'l':
            return "long";
        case 'j':
            return "unsigned int";
        case 's':
            return "short";
        case 't':
            return "unsigned short";
        case 'x':
            return "long long";
        case 'y':
            return "unsigned long long";
        case 'b':
            return "bool";
        default:
            return name;
    }
}

template<typename T>
void printType() {
    string name = typeid(T).name();
    printTypeById(name);
}

Neurone::Neurone(vector<int> model) : Generator() {
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

Neurone::Neurone(char *nameImportReseau) : Generator(nameImportReseau) {}

Neurone::Neurone(vector<int> model, char *nameImportReseau) : Generator(model, nameImportReseau) {}

Neurone::~Neurone() {}

double Neurone::sigmoide(double x) {
    if (x > 709)
        return 1;
    else if (x < -709) 
        return 0;
    else
        return 1 / (1 + exp(-x));
}

double Neurone::sigmoid_derivee(double x) {
    double sigmoide = Neurone::sigmoide(x);
    return sigmoide * (1 - sigmoide);
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
    int avancement = 1;

    for (vector< vector<double> > couche : reseau) {
        resultCouche.push_back(vector<double> ());
        for (vector<double> neurone : couche) {
            resultCouche[avancement].push_back(Neurone::calculForward(neurone, entree));
        }
        entree = resultCouche[avancement++];
    }

    return entree;
}

void Neurone::backward(vector<double> &sortieAttendu) {

    for (int avancement = reseau.size() - 1, indexResult = resultCouche.size() - 1; avancement >= 0; avancement--) {
        vector<double> erreur;
        for (int index = 0; index < resultCouche[indexResult].size(); index++) {
            erreur.push_back(sortieAttendu[index] - resultCouche[indexResult][index]);
        }

        vector<double> erreurDelta;
        for (int index = 0; index < erreur.size(); index++) {
            erreurDelta.push_back(erreur[index] - Neurone::sigmoid_derivee(resultCouche[indexResult][index]));
        }

        sortieAttendu = erreurDelta;
        --indexResult;

        // cout << reseau[avancement].size() << "|";
        for (int indexNeurone = 0; indexNeurone < reseau[avancement].size(); indexNeurone++) {
            // cout << reseau[avancement][indexNeurone].size();
            for (int index = 0; index < reseau[avancement][indexNeurone].size(); index++) {
                // cout << ":" << reseau[avancement][indexNeurone][index] << "->" << reseau[avancement][indexNeurone][index] + resultCouche[indexResult][index] * erreurDelta[indexNeurone];
                // cout << endl << reseau[avancement][indexNeurone][index] << " + " << resultCouche[indexResult][index] << " * " << erreurDelta[indexNeurone];
                reseau[avancement][indexNeurone][index] = reseau[avancement][indexNeurone][index] + resultCouche[indexResult][index] * erreurDelta[indexNeurone];
                // cout << ":" << reseau[avancement][indexNeurone][index] << endl;
            }
            // cout << endl;
        }
    }
}

vector<double> Neurone::prediction(vector<double> entree) {
    return forward(entree);
}

void Neurone::entrainement(vector<double> entree, vector<double> sortieAttendu) {
    forward(entree);
    backward(sortieAttendu);
}

void Neurone::entrainement(vector< vector<double> > entree, vector< vector<double> > sortieAttendu) {
    if (entree.size() != sortieAttendu.size()) {
        cout << "ERROR : not good training input : take " << entree.size() << " input, and " << sortieAttendu.size() << " output correction" << endl;
        return;
    }

    for (int index = 0; index < entree.size(); index++) {
        forward(entree[index]);
        backward(sortieAttendu[index]);
    }
    cout << "end training" << endl;
}

