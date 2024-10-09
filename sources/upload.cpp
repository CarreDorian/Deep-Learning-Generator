#include "../includes/upload.h"

File::File() : fileName("") {}

File::File(char *newFileName) : fileName(newFileName) {}

void File::chargeFileName(char *newFileName) {
    fileName = newFileName;
}

vector< vector< vector<double> > > File::read() {
    ifstream file(fileName);
    vector< vector< vector<double> > > poids;
    vector< vector<double> > couche;
    vector<double> sousCouche;
    int placeLine = 0;
    string line;
    double nbr = 0, dizaine = 0;

    if (!file.good()) {
        std::cout << "ERREUR : fichier " << fileName << " unfined" << std::endl;
        return poids;
    }
    
    while (getline(file, line)) {
        placeLine++;
        int placeCarac = 0;

        for (char carac : line) {
            placeCarac++;

            if (dizaine == 0) {
                if (carac == '\t') {
                    dizaine = 10;
                }

                continue;
            }
            double to_add;

            switch (carac) {
            case '\n':
            case '\r':
            case '\0':
                break;
            
            case 'W':
                if (sousCouche.size() > 0) {
                    sousCouche.push_back(nbr);
                    couche.push_back(sousCouche);
                    poids.push_back(couche);
                    sousCouche.clear();
                    couche.clear();
                    dizaine = 0;
                    nbr = 0;
                }

                break;

            case ';':
                sousCouche.push_back(nbr);
                nbr = 0;
                dizaine = 10;
                break;

            case '\t':
                sousCouche.push_back(nbr);
                nbr = 0;
                dizaine = 10;
                couche.push_back(sousCouche);
                sousCouche.clear();
                break;

            case '.':
            case ',':
                dizaine = 0.1;
                break;

            default:
                to_add = (carac - 48);
                if (to_add < 0 || to_add > 9) {
                    cout << "ERROR : bad character in file : " << fileName << ":" << placeLine << ":" << placeCarac << "." << endl;
                    return vector< vector< vector<double> > >();
                }

                if (dizaine < 1) {
                    to_add *= dizaine;
                    dizaine *= 0.1;
                } else
                    nbr *= dizaine;
                nbr += to_add;
            }

        }
    }
    if (sousCouche.size() > 0) {
        sousCouche.push_back(nbr);
        couche.push_back(sousCouche);
        poids.push_back(couche);
        sousCouche.clear();
        couche.clear();
    }

    file.close();
    return poids;
}

void File::write(vector< vector< vector<double> > > poids) {
    ofstream file(fileName);
    int count = 1;
    
    for (vector< vector<double> > coucheNeurones : poids) {
        file << "W" << count++;
        for (vector<double> couche : coucheNeurones) {
            file << "\t";
            string str = "";
            for (double neurone : couche) {
                str += to_string(neurone) + ";";
            }
            str.erase(str.size() - 1); 
            file << str << endl;
        }
    }

    file.close();
}