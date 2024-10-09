#ifndef FILE
// FILE sera défini dans l'include suivant
#include "upload.h"
#endif

#ifndef RANDOM
#define RANDOM
#include <random>
#endif

#ifndef GENERETOR
#define GENERETOR

double nbrAleatoire();

class Generator : public File {
public:
    vector< vector< vector<double> > > reseau;

    using File::read;
    using File::write;

public:
    Generator();
    Generator(vector<int> model);
    Generator(char *nameImportReseau);
    Generator(vector<int> model, char *nameImportReseau);
    ~Generator();
    vector< vector< vector<double> > > getModel();
    void showModel();
    void addToBeginReseau(vector<int> model);
    void addToEndReseau(vector<int> model);
    void modelFusion(char *nameImportReseau);
    void chargeModel(vector< vector< vector<double> > > newReseau);
    void chargeModel();
    void saveModel();
};

#endif