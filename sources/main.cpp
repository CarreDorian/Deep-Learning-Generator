#include "../includes/upload.h"
#include "../includes/neurones.h"

int main() {

    vector<int> test(3,3);
    test.push_back(5);
    test.push_back(2);
    test.push_back(5);
    Neurone Einstein(test);
    Einstein.showModel();

    // vector< vector<float> > poids(3, vector<float> (5, 3.53));
    // char *fileName = "test.txt";

    // File data(fileName);

    // data.write(poids);
    // poids.clear();
    // poids = data.read();

    // int count = 0;
    // for (auto line : poids) {
    //     cout << "W" << ++count;
    //     for (float i : line) {
    //         cout << '\t' << i;
    //     }
    //     cout << endl;
    // }

    return 0;
}