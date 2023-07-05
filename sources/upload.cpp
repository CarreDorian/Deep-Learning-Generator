#include "../includes/upload.h"

File::File() : fileName("") {}

File::File(char *newFileName) : fileName(newFileName) {}

void File::chargeFileName(char *newFileName) {
    fileName = newFileName;
}

vector< vector< vector<float> > > File::read() {
    ifstream file(fileName);
    vector< vector< vector<float> > > poids;
    vector< vector<float> > couche;
    vector<float> sousCouche;
    int placeLine = 0;
    string line;
    float nbr = 0, dizaine = 0;
    
    while (std::getline(file, line)) {
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
            float to_add;

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
                    return vector< vector< vector<float> > >();
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

void File::write(vector< vector< vector<float> > > poids) {
    ofstream file(fileName);
    int count = 1;
    
    for (vector< vector<float> > coucheNeurones : poids) {
        file << "W" << count++;
        for (vector<float> couche : coucheNeurones) {
            file << "\t";
            string str = "";
            for (float neurone : couche) {
                str += to_string(neurone) + ";";
            }
            str.erase(str.size() - 1); 
            file << str << endl;
        }
    }

    file.close();
}