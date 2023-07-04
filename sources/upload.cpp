#include "../includes/upload.h"

File::File() : fileName("") {}

File::File(char *newFileName) : fileName(newFileName) {}

void File::chargeFileName(char *newFileName) {
    fileName = newFileName;
}

vector< vector<float> > File::read() {
    ifstream file(fileName);
    vector< vector<float> > poids;
    vector<float> couche;
    int placeLine = 0;
    string line;

    
    while (std::getline(file, line)) {
        placeLine++;
        int placeCarac = 0;
        double dizaine = 0, multiplicateur = 10;
        float nbr = 0;

        for (char carac : line) {
            placeCarac++;

            if (dizaine == 0) {
                if (carac == '\t') {
                    dizaine = 1;
                }

                continue;
            }

            switch (carac) {
            case '\n':
            case '\r':
                if (couche.size() > 0) {
                    couche.push_back(nbr);
                    poids.push_back(couche);
                    couche.clear();
                    dizaine = 0;
                    nbr = 0;
                    multiplicateur = 10;
                }

                break;

            case '\t':
                couche.push_back(nbr);
                nbr = 0;
                dizaine = 1;
                multiplicateur = 10;
                break;

            case '.':
            case ',':
                dizaine = 0.1;
                multiplicateur = 0.1;
                break;

            default:
                carac -= 48;
                if (carac < 0 || carac > 9) {
                    cout << "ERROR : bad caracter in file : " << fileName << ":" << placeLine << ":" << placeCarac << "." << endl;
                }
                nbr += carac * dizaine;
                dizaine *= multiplicateur;
            }
        }

        if (couche.size() > 0) {
            couche.push_back(nbr);
            poids.push_back(couche);
            couche.clear();
        }
    }

    file.close();
    return poids;
}

void File::write(vector< vector<float> > poids) {
    ofstream file(fileName);
    int count = 1;
    
    for (vector<float> couche : poids) {
        file << "W" << count++;
        for (float neurone : couche) {
            file << "\t" << neurone;
        }
        file << endl;
    }

    file.close();
}