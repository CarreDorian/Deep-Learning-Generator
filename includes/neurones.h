#include "upload.h"

#ifndef RANDOM
#define RANDOM
#include <random>
#endif

#ifndef NEURONE
#define NEURONE

float nbrAleatoire();

class Neurone {
private:
    vector< vector<float> > reseau;

public:
    Neurone(vector<int> model);
    void showModel();
};

#endif
