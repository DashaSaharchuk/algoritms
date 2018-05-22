#include "matrixlimitation.h"

MatrixLimitation::MatrixLimitation()
{
    line.push_back(Frac(0.0));
    line.push_back(Frac(0.0));
    lim = 0;
}

MatrixLimitation::MatrixLimitation(vector<Frac> task, int limit)
{
    line = task;
    lim = limit;
}

void MatrixLimitation::setLine(vector<Frac> task)
{
    line = task;
}

vector<Frac> MatrixLimitation::getLine()
{
    return line;
}

void MatrixLimitation::setLimit(int limit)
{
    lim = limit;
}

int MatrixLimitation::getLimit()
{
    return lim;
}
