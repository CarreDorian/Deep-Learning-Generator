#include "generator.h"

#ifndef NEURONE
#define NEURONE

double nbrAleatoire();

class Neurone : public Generator {
protected:
    vector< vector< vector<double> > > reseau;
    vector< vector<double> > resultCouche;

    double sigmoide(double x);
    double sigmoid_derivee(double x);
    double calculForward(vector<double> neurone, vector<double> entree);
    vector<double> forward(vector<double> entree);
    void backward(vector<double> sortieAttendu);


public:
    vector<double> prediction(vector<double> entree);
    void entrainement(vector<double> entree, vector<double> sortieAttendu);
    void entrainement(vector< vector<double> > entree, vector< vector<double> > sortieAttendu);
};

#endif