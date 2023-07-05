#include "upload.h"

#ifndef RANDOM
#define RANDOM
#include <random>
#endif

#ifndef NEURONE
#define NEURONE

float nbrAleatoire();

class Neurone : public File {
protected:
    vector< vector< vector<float> > > reseau;

    using File::read;
    using File::write;

public:
    Neurone(vector<int> model);
    Neurone(char *importReseau);
    Neurone(vector<int> model, char *importReseau);
    void showModel();
    vector< vector< vector<float> > > getModel();
    void chargeModel(vector< vector< vector<float> > > newReseau);
    void chargeModel();
    void saveModel();
    vector<float> forward(vector<float> entree);
    void backward();
};

#endif