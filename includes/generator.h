#include "upload.h"

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
    void chargeModel(vector< vector< vector<double> > > newReseau);
    void chargeModel();
    void saveModel();
};

#endif