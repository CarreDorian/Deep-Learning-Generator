#ifndef INCLUDES
#define INCLUDES
#include "includes.h"
#endif

#ifndef FILE
#define FILE

class File {
protected:
    char *fileName;

public:
    File();
    File(char *newFileName);
    void chargeFileName(char *newFileName);
    vector< vector<float> > read();
    void write(vector< vector<float> > poids);
};

#endif
