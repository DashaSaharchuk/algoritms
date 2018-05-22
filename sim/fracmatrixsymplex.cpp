#include "fracmatrixsymplex.h"

using namespace std;

FracMatrixSymplex::FracMatrixSymplex(Frac **matrix, int x, int y, bool isMin, bool fake) : m(matrix), xsize(x), ysize(y)
{
    toMin = isMin;
    isFake = fake;
    if(toMin && isFake) {
        xmainvar = xsize - 2;
    } else {
        xmainvar = xsize - 1;
    }
    setNewSnapshot();
}

FracMatrixSymplex::FracMatrixSymplex(vector <MatrixLimitation> matrix, MatrixLimitation target)
{
    //all limitations is equal length
//    vector <Frac> buffer;
//    for(int i = 0; i < matrix[0].getLine().size(); ++i) {
//        m2.push_back(buffer);
//        for(int j = 0; j < matrix.size(); ++j) {
//            m2[i].push_back(matrix[j].getLine()[i]);
//        }
//    }

    m2.resize(matrix[0].getLine().size());
    for(unsigned int i = 0; i < matrix.size(); ++i) {
        rowInsert(i, matrix[i].getLine());
    }
    rowInsert(matrix.size(), target.getLine());

    int basei = 0;
    for(unsigned int i = 0; i < matrix.size(); ++i) {
        vector<Frac> buffer;
        buffer.resize(m2[0].size());
        switch(matrix[i].getLimit()) {
        case MLIMIT_EQSMALLER:
            buffer[basei] = Frac(1, 1);
            colInsert(m2.size() - 1, buffer);
            basei++;
            break;
        case MLIMIT_EQBIGGER:
            buffer[basei] = Frac(1, 1);
            colInsert(m2.size() - 1, buffer);
            rowMulti2(basei, Frac(-1, 1));
            basei++;
            break;
            // cases for all
        }
        buffer.clear();
    }

//    vector <Frac> matrBuff; // buffer for limitations/pointerf
//    for(unsigned int i = 0; i < m2[0].size(); ++i) {
//        matrBuff = matrix[i].getLine();
//        for(unsigned int j = 0; j < m2.size(); ++j) {
//            m2[j][i] = matrBuff[j];
//        }
//        matrBuff.clear();
//    }

//    for(unsigned int i = 0; i < m2.size(); ++i) {
//        m2[i].resize(matrix.size() + 1);
//    }
//    matrBuff = target.getLine();
//    for(unsigned int j = 0; j < m2.size(); ++j) {
//        m2[j][m2[0].size() - 1] = matrBuff[j];
//    }
//    cout << endl << endl << "constructor:" << endl;
//    for(unsigned int i = 0; i < m2[0].size(); ++i) {
//        for(unsigned int j = 0; j < m2.size(); ++j) {
//            cout << m2[j][i] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;


//    xsize = matrix.size();
//    ysize = 0;
//    int numOfAddVar = 0; // after m[i][numOfAddVar] - artifical variables
//    int numOfMainVar = 0;

//    for(int i = 0; i < matrix.size(); ++i) { // def size
//        if(ysize < matrix[i].getLine().size())
//            ysize = matrix[i].getLine().size();
//    }
//    numOfMainVar = ysize;

//    for(int i = 0; i < matrix.size(); ++i) { // def num of additional variables
//        int bufLim = matrix[i].getLimit();
//        if(bufLim != 0) {
//            if(bufLim < 0)
//                ysize++;
//            if(bufLim > 0) {
//                ysize += 2;
//            }
//            numOfAddVar++;
//        }
//    }

//    int addVarCount = 0, addVarArtifCount = 0;

//    m = new Frac *[xsize + 1];
//    if(target.getLimit() > 0) {
//        for(int i = 0; i < xsize; ++i) {
//            m[i] = new Frac[ysize];
//            for(int j = 0; j < ysize; ++j) {
//                m[i][j] = matrix[i].getLine()[j];
//            }

//            switch(matrix[i].getLimit()) {
//            case 1:
//                m[i][numOfMainVar + addVarCount] = -1.0;
//                m[i][numOfMainVar + numOfaddVar + addVarArtifCount] = 1.0;
//                addVarCount++;
//                break;

//            case -1:
//                m[i][numOfMainVar + addVarCount] = 1.0;
//                addVarCount++;
//                break;
//            }

//        }
//        m[xsize] = new Frac[ysize];
//        for(int j = 0; j < ysize; ++j) {
//            m[xsize][j] = target.getLine()[j];
//        }
//        isMin = false;
//    }

//    if(target.getLimit() < 0) {
//        for(int i = 0; i < xsize; ++i) {
//            m[i] = new Frac[ysize];
//            for(int j = 0; j < ysize; ++j) {
//                m[i][j] = matrix[i].getLine()[j];
//            }
//        }
//        m[xsize] = new Frac[ysize];
//        for(int j = 0; j < ysize; ++j) {
//            m[xsize][j] = target.getLine()[j];
//        }
//        isMin = true;
//    }
}

void FracMatrixSymplex::rowAdd(int row, Frac *add)
{
    for(int i = 0; i < ysize; ++i) {
        m[row][i] += add[i];
    }
}

void FracMatrixSymplex::rowMulti(int row, Frac mult)
{
    for(int i = 0; i < ysize; ++i)
        m[row][i] *= mult;
}

void FracMatrixSymplex::colMulti(int col, Frac mult)
{
    for(int i = 0; i < xsize; ++i)
        m[i][col] *= mult;
}

void FracMatrixSymplex::rowInsert(int row, vector<Frac> add)
{

    for(unsigned int i = 0; i < m2.size(); ++i) {
        vector<Frac>::iterator it = m2[i].begin() + row;
        m2[i].insert(it, add[i]);
    }
}

void FracMatrixSymplex::colInsert(int col, vector<Frac> add)
{
    if(add.size() != m2[0].size())
        add.resize(m2[0].size());
    vector<vector<Frac>>::iterator it = m2.begin() + col;
    m2.insert(it, add);
}

void FracMatrixSymplex::rowAdd(int row, vector<Frac> add)
{
    if(add.size() != m2.size()) {
        cout << "Error in rowAdd<" << row << ">" << endl;
        return;
    }
    for(unsigned int i = 0; i < m2.size(); ++i) {
        m2[i][row] += add[i];
    }
}

void FracMatrixSymplex::rowMulti2(int row, Frac mult)
{
    for(unsigned int i = 0; i < m2.size(); ++i) {
        m2[i][row] *= mult;
    }
}

void FracMatrixSymplex::colMulti2(int col, Frac mult)
{
    for(unsigned int i = 0; i < m2[col].size(); ++i)
        m2[col][i] *= mult;
}

bool FracMatrixSymplex::setNewSnapshot()
{
    Frac **snapshot;
    snapshot = new Frac *[xsize];
    for(int i = 0; i < xsize; ++i) {
        snapshot[i] = new Frac[ysize];
        for(int j = 0; j < ysize; ++j) {
            snapshot[i][j] = m[i][j];
        }
    }
    bool res;
    for(unsigned int i = 0; i < baseSnapshot.size(); ++i) {
        res = true;
        for(int j = 0; j < xsize; ++j) {
            for(int k = 0; k < ysize; ++k) {
                if(!(snapshot[j][k] == (baseSnapshot[i].first)[j][k])) {
                    res = false; // vector[i] is diff
                    break; // its useless for us now
                }
            }
        }
        if(res == true) // if snapshot is equal vector[i]
            return false;
    }
    //snapshot is original
    int *baseSnap = new int[ysize];
    for(int i = 0; i < ysize; ++i) {
        int b = columnIsBasis(i);
        if(b != -1) {
            baseSnap[i] = b + 1;
        } else {
            baseSnap[i] = 0;
        }
    }
    baseSnapshot.push_back(make_pair(snapshot, baseSnap));
//    cout << "SNAPSHOT: <";
//    for(int i = 0; i < ysize; ++i) {
//        cout << baseSnapshot[baseSnapshot.size() - 1].second[i] << " ";
//    }
//    cout << "\b>" << endl;

//    for(int i = 0; i <= xsize; ++i) {
//        for(int j = 0; j < ysize; ++j) {
//            baseSnapshot[baseSnapshot.size() - 1].first[i][j].print();
//            cout << " ";
//        }
//        cout << endl;
//    }
    return true;
}

int FracMatrixSymplex::columnIsBasis(int col)
{
    int basisRow = -1;
    for(int i = 0; i < xmainvar; ++i) {
        if(m[i][col] == 1) {
            if(basisRow == -1) {
                basisRow = i;
            } else {
                return -1;
            }
        } else {
            if(m[i][col] != 0)
                return -1;
        }
    }
    return basisRow;
}

void FracMatrixSymplex::symplexMethod()
{
    int lRow, lCol;
    cout << endl << "START M:" << endl;
    printMatrix();
    cout << endl << endl;
    if(toMin && isFake) {
        setZeroInArtif();
    }
    while(!isOptimal()) {
        findLeadForBasisPlan(lRow, lCol);
        rectangleMethod(lRow, lCol);
        printMatrix();
        if(!setNewSnapshot())
            break;
    }
}

bool FracMatrixSymplex::rebase(int inputColumn, int outputColumn)
{
    int basisRow = -1;
    // check that output column is basis and that input column wasn't basis before
    basisRow = columnIsBasis(outputColumn);
    if(basisRow == -1 || columnIsBasis(inputColumn) != -1) // basisRow is the num of row that is not null in output basis
        return false;

    setBasisInColumn(inputColumn, basisRow);
    setNewSnapshot();
    return true;
}

void FracMatrixSymplex::printMatrix()
{
    cout << "Matrix:" << endl;
    for(int i = 0; i < xmainvar; ++i) {
        for(int j = 0; j < ysize; ++j) {
            m[i][j].print();
            cout << " ";
        }
        cout << endl;
    }

    cout << "Target function:" << endl;
    for(int i = xmainvar; i < xsize; ++i) {
        for(int j = 0; j < ysize - 1; ++j) {
            if(!toMin)
                (m[i][j] * -1.0).print();
            else
                m[i][j].print();
            cout << "*x[" << j + 1 << "] + ";
        }
        cout << "\b\b";
        cout << "= ";
        if(toMin && isFake)
            (m[i][ysize - 1] * -1.0).print();
        else
            m[i][ysize - 1].print();
        cout << endl;
    }
}

void FracMatrixSymplex::setBasis(int *columns)
{
    for(int i = 0; i < xmainvar; ++i) {
        setBasisInColumn(columns[i], i);
    }
}

bool FracMatrixSymplex::basisWasBefore(int *columns)
{
    bool res;
    for(unsigned int i = 0; i < baseSnapshot.size(); ++i) { // for every snapshot...
        res = true;
        for(int j = 0; j < xmainvar; ++j) { // if input basis was exist, res will be true
            if(columns[j] != (baseSnapshot[i].second)[j]) {
                res = false;
                break;
            }
        }
        if(res)
            return res;
    }
    return false;
}

void FracMatrixSymplex::setZeroInArtif()
{
    for(int bi = 0; bi < xmainvar; ++bi) {
        int i = ysize - 2 - bi;
        int basRow = columnIsBasis(i);
        if(basRow == -1) {
            cout << "CRITICAL ERROR! CRITICAL ERROR!" << endl;
            return;
        }
        Frac a = m[xsize - 1][i];
        for(int j = 0; j < ysize; ++j) {
            m[xsize - 1][j] -= m[basRow][j] * a;
        }
    }
}

ostream &operator<<(ostream &str, FracMatrixSymplex &outMatrix)
{
    for(unsigned int i = 0; i < outMatrix.xsize; ++i) {
        for(unsigned int j = 0; j < outMatrix.ysize; ++j) {
            str << outMatrix.m[i][j] << " ";
        }
        str << endl;
    }
    return str;
}

void FracMatrixSymplex::setBasisInColumn(int column, int row)
{
    Frac *bufRow = new Frac[ysize]; // buffer for making '0'
    rowMulti(row, m[row][column].invert()); // making '1' in m[row][column]
    for(int i = 0; i < xsize; ++i) { // for every row

        if(i != row) {
            for(int j = 0; j < ysize; ++j) { // "(i) - (row) * m[i][column]"
                bufRow[j] = m[row][j] * m[i][column] * -1.0;
            }
            rowAdd(i, bufRow);
        }
    }
    delete bufRow;
}

void FracMatrixSymplex::findOptForBasisPlan(int &optimalRow, int &optimalCol)
{
    Frac min = m[0][ysize - 1];
    for(int i = 1; i < xsize; ++i) {
        if(m[i][ysize - 1] < 0.0)
            if(m[i][ysize - 1] < min) {
                min = m[i][ysize - 1];
                optimalRow = i;
            }
    }

    optimalCol = 0;
    min = m[optimalRow][0];
    for(int j = 1; j < ysize; ++j) {
        if(m[optimalRow][j] < min) {
            min = m[optimalRow][j];
            optimalCol = j;
        }
    }
    if(min > 0.0 && min == 0.0) {
        cout << "CRITICAL ERROR! WTF IS GOING ON!" << endl;
    }


}

void FracMatrixSymplex::findLeadForBasisPlan(int &leadRow, int &leadCol)
{
    leadCol = 0;
    Frac min = (m[xsize - 1][0] < 0.0) ? m[xsize - 1][0] : 0.0;
    if(toMin && !isFake) {
        for(int i = 0; i < ysize - 1; ++i) {
            if(m[xsize - 1][i] > 0.0) {
                leadCol = i;
                break;
            }
        }
    } else {
        for(int i = 0; i < ysize - 1; ++i) {
            if(m[xsize - 1][i] < min) {
                min = m[xsize - 1][i];
                leadCol = i;
            }
        }
    }

    leadRow = 0;
    Frac k = (m[0][ysize - 1] / m[0][leadCol]);
    for(int i = 1; i < xmainvar; ++i) {
        Frac kbuf = m[i][ysize - 1] / m[i][leadCol];
        if(k > 0) {
            if(kbuf < k && kbuf > 0.0) {
                leadRow = i;
                k = kbuf;
            }
        } else {
            if(kbuf > 0.0) {
                leadRow = i;
                k = kbuf;
            }
        }
    }
    cout << "Lead for basis plan:" << leadRow << " " << leadCol << endl;
}

void FracMatrixSymplex::rectangleMethod(int optRow, int optColumn)
{
    cout << "Multiplcation: (" << optRow << ") * ";
    m[optRow][optColumn].invert().print();
    cout << endl;
    rowMulti(optRow, m[optRow][optColumn].invert());
    for(int i = 0; i < xsize; ++i) {
        if(i != optRow)
            for(int j = 0; j < ysize; ++j) {
                if(j != optColumn) {
                    m[i][j] = m[i][j] - (m[i][optColumn] * m[optRow][j] / m[optRow][optColumn]);
                }
            }
    }
    for(int i = 0; i < xsize; ++i)
        if(i != optRow)
            m[i][optColumn] = 0;
}

bool FracMatrixSymplex::isOptimal()
{
    for(int i = 0; i < ysize; ++i) {
        if(toMin && isFake) {
            if(m[xsize - 1][i] > 0.0) {
                return false;
            }
        } else {
            if(m[xsize - 1][i] < 0.0) {
                return false;
            }
        }
    }
    return true;
}


