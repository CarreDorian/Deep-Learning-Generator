#include "../includes/upload.h"
#include "../includes/neurones.h"

int main() {

    vector<int> test(3,3);
    test.push_back(5);
    test.push_back(2);
    test.push_back(5);
    Neurone Einstein(test, "test.txt");
    Einstein.showModel();
    // Einstein.saveModel();

    Einstein.chargeModel();
    Einstein.showModel();

    test.push_back(5);
    test.push_back(2);
    test.push_back(5);

    Neurone EinsteinBis(test);
    EinsteinBis.showModel();
    
    EinsteinBis.chargeModel(Einstein.getModel());
    EinsteinBis.showModel();


    // vector< vector<double> > poids(3, vector<double> (5, 3.53));
    // char *fileName = "test.txt";

    // File data(fileName);

    // data.write(poids);
    // poids.clear();
    // poids = data.read();

    // int count = 0;
    // for (auto line : poids) {
    //     cout << "W" << ++count;
    //     for (double i : line) {
    //         cout << '\t' << i;
    //     }
    //     cout << endl;
    // }

    return 0;
}