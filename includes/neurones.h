#include "upload.h"

#ifndef RANDOM
#define RANDOM
#include <random>
#endif

#ifndef NEURONE
#define NEURONE

double nbrAleatoire();

class Neurone : public File {
protected:
    vector< vector< vector<double> > > reseau;
    vector< vector<double> > resultCouche;

    using File::read;
    using File::write;

public:
    Neurone(vector<int> model);
    Neurone(char *importReseau);
    Neurone(vector<int> model, char *importReseau);
    void showModel();
    vector< vector< vector<double> > > getModel();
    void chargeModel(vector< vector< vector<double> > > newReseau);
    void chargeModel();
    void saveModel();
    double sigmoide(double x);
    double sigmoid_derivee(double x)
    double calculForward(vector<double> neurone, vector<double> entree);
    vector<double> forward(vector<double> entree);
    void backward();
};

#endif