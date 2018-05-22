#ifndef FRAC_H
#define FRAC_H

#include <cmath>
#include <cstdio>
#include <fstream>
#define SM_PRES 1000
#define PRES 1000000
#define BG_PRES 1000000000

enum FRAC_VISUAL {
    IMPROP,
    PROP
};

class Frac
{
    public:
        Frac();

        Frac(int a, int b);

        Frac(double num, int pres = 1000000);

        //+-*/

        Frac operator+ (const Frac& sec);
        Frac operator+ (const double& sec);
        Frac operator- (const Frac& sec);
        Frac operator- (const double& sec);
        Frac operator* (const Frac& sec);
        Frac operator* (const double& sec);
        Frac operator/ (const Frac& sec);
        Frac operator/ (const double& sec);

        //+-*/=

        Frac operator+= (const Frac& sec);
        Frac operator+= (const double& sec);
        Frac operator-= (const Frac& sec);
        Frac operator-= (const double& sec);
        Frac operator*= (const Frac& sec);
        Frac operator*= (const double& sec);
        Frac operator/= (const Frac& sec);
        Frac operator/= (const double& sec);

        //<>==

        bool operator> (const Frac& sec);
        bool operator> (const double& sec);
        bool operator< (const Frac& sec);
        bool operator< (const double& sec);
        bool operator== (const Frac& sec);
        bool operator== (const double& sec);
        bool operator!= (const Frac& sec);
        bool operator!= (const double& sec);

        //input, output
        friend std::ostream &operator<<(std::ostream &str, Frac& outFrac);
        friend std::istream &operator>>(std::istream &str, Frac& inFrac);

        Frac invert();
        Frac pow(int x);
        Frac abs();

        void setNewNum(int newNumer, int newDenom);
        int intPart();
        Frac fracPart();
        double toDouble();
        void print(FRAC_VISUAL regime = IMPROP);
private:
        int numer;
        int denom;
        int GCD(int a, int b);
        int LCM(int a, int b);
        void toShorten();
        void setSign();
};


#endif // FRAC_H
