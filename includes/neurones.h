#include "generator.h"
#include "includes.h"

#ifndef NEURONE
#define NEURONE

string printTypeById(string name);

class Neurone : public Generator {
protected:
    vector< vector<double> > resultCouche;

    double sigmoide(double x);
    double sigmoid_derivee(double x);
    double calculForward(vector<double> neurone, vector<double> entree);
    vector<double> forward(vector<double> entree);
    void backward(vector<double> &);


public:
    Neurone(vector<int> model);
    Neurone(char *importReseau);
    Neurone(vector<int> model, char *importReseau);
    ~Neurone();
    vector<double> prediction(vector<double> entree);
    void entrainement(vector<double> entree, vector<double> sortieAttendu);
    void entrainement(vector< vector<double> > entree, vector< vector<double> > sortieAttendu);
};

#endif