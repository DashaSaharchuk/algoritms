#ifndef MATRIXLIMITATION_H
#define MATRIXLIMITATION_H

#include "frac.h"
#include <vector>

#define MLIMIT_EQSMALLER -1
#define MLIMIT_EQUAL 0
#define MLIMIT_EQBIGGER 1

using namespace std;

class MatrixLimitation
{
public:
    MatrixLimitation();
    MatrixLimitation(vector <Frac> task, int limit = MLIMIT_EQUAL);
    void setLine(vector <Frac> task);
    vector <Frac> getLine();
    void setLimit(int limit);
    int getLimit();

private:
    vector <Frac> line; // started from free
    int lim;
    /*
     * limit:
     * -1 - eqsmaller || to min
     * 0 - equal
     * 1 - eqbigger || to max
     * */
};

#endif // MATRIXLIMITATION_H
