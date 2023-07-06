#include "upload.h"

#ifndef RANDOM
#define RANDOM
#include <random>
#endif

#ifndef GENERETOR
#define GENERETOR

double nbrAleatoire();

class Generator : public File {
protected:
    vector< vector< vector<double> > > reseau;

    using File::read;
    using File::write;

public:
    Generator(vector<int> model);
    Generator(char *importReseau);
    Generator(vector<int> model, char *importReseau);
    void showModel();
    vector< vector< vector<double> > > getModel();
    void chargeModel(vector< vector< vector<double> > > newReseau);
    void chargeModel();
    void saveModel();
};

#endif