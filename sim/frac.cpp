#include "frac.h"



Frac::Frac() : numer(0), denom(1) {}

Frac::Frac(int a, int b) {
    if(b) {
        numer = a;
        denom = b;
        toShorten();
        setSign();
    } else {
        numer = 0;
        denom = 1;
    }
}

Frac::Frac(double num, int pres) {
    if(pres <= 0) {
        numer = 0;
        denom = 1;
    } else {
        numer = (int) (num * pres);
        denom = pres;
        toShorten();
        setSign();
    }
}

Frac Frac::operator+(const Frac &sec) {
    int resDenom = LCM(this->denom, sec.denom);
    int resNumer = this->numer * (resDenom / this->denom) + sec.numer * (resDenom / sec.denom);
    Frac res(resNumer, resDenom);
    return res;
}

Frac Frac::operator+(const double &sec) {
    Frac tmpSec(sec);
    Frac res = *this + tmpSec;
    return res;
}

Frac Frac::operator-(const Frac &sec) {
    int resDenom = LCM(this->denom, sec.denom);
    int resNumer = this->numer * (resDenom / this->denom) - sec.numer * (resDenom / sec.denom);
    Frac res(resNumer, resDenom);
    return res;
}

Frac Frac::operator-(const double &sec) {
    Frac tmpSec(sec);
    Frac res = *this - tmpSec;
    return res;
}

Frac Frac::operator*(const Frac &sec) {
    int resDenom = this->denom * sec.denom;
    int resNumer = this->numer * sec.numer;
    Frac res(resNumer, resDenom);
    return res;
}

Frac Frac::operator*(const double &sec) {
    Frac tmpSec(sec);
    Frac res = *this * tmpSec;
    return res;
}

Frac Frac::operator/(const Frac &sec) {
    int resDenom = this->denom * sec.numer;
    int resNumer = this->numer * sec.denom;
    Frac res(resNumer, resDenom);
    return res;
}

Frac Frac::operator/(const double &sec) {
    Frac tmpSec(sec);
    Frac res = *this / tmpSec;
    return res;
}

Frac Frac::operator+=(const Frac &sec) {
    *this = *this + sec;
    return *this;
}

Frac Frac::operator+=(const double &sec) {
    Frac tmpSec(sec);
    *this = *this + tmpSec;
    return *this;
}

Frac Frac::operator-=(const Frac &sec) {
    *this = *this - sec;
    return *this;
}

Frac Frac::operator-=(const double &sec) {
    Frac tmpSec(sec);
    *this = *this - tmpSec;
    return *this;
}

Frac Frac::operator*=(const Frac &sec) {
    *this = *this * sec;
    return *this;
}

Frac Frac::operator*=(const double &sec) {
    Frac tmpSec(sec);
    *this = *this * tmpSec;
    return *this;
}

Frac Frac::operator/=(const Frac &sec) {
    *this = *this / sec;
    return *this;
}

Frac Frac::operator/=(const double &sec) {
    Frac tmpSec(sec);
    *this = *this / tmpSec;
    return *this;
}

bool Frac::operator>(const Frac &sec) {
    Frac resNumer = *this - sec;
    return resNumer.numer > 0;
}

bool Frac::operator>(const double &sec) {
    Frac tmpSec(sec);
    return *this > tmpSec;
}

bool Frac::operator<(const Frac &sec) {
    Frac resNumer = *this - sec;
    return resNumer.numer < 0;
}

bool Frac::operator<(const double &sec) {
    Frac tmpSec(sec);
    return *this < tmpSec;
}

bool Frac::operator==(const Frac &sec) {
    Frac resNumer = *this - sec;
    return resNumer.numer == 0;
}

bool Frac::operator==(const double &sec) {
    Frac tmpSec(sec);
    return *this == tmpSec;
}

bool Frac::operator!=(const Frac &sec)
{
    Frac resNumer = *this - sec;
    return !(resNumer.numer == 0);
}

bool Frac::operator!=(const double &sec)
{
    Frac tmpSec(sec);
    return (*this != tmpSec);
}


std::ostream &operator<<(std::ostream &str, Frac &outFrac)
{
    str << "(" << outFrac.numer << "/" << outFrac.denom << ")";
    return str;
}

std::istream &operator>>(std::istream &str, Frac &inFrac)
{
    int num, den;
    char buffer;
    str >> num >> buffer >> den;
    if(buffer == '/' && den != 0) {
        inFrac.numer = num;
        inFrac.denom = den;
    } else {
        inFrac.numer = 0;
        inFrac.denom = 1;
    }
    return str;
}

Frac Frac::invert() {
    Frac tmp (denom, numer);
    return tmp;
}

Frac Frac::pow(int x) {
    Frac tmp(numer, denom);
    if(x < 0) {
        tmp = tmp.invert();
        x *= -1;
    }

    Frac res = tmp;
    for(int i = 0; i < x; ++i) {
        res = res * tmp;
    }

    return res;
}

Frac Frac::abs()
{
    if(*this > 0.0) {
        return *this;
    } else {
        return (*this * -1.0);
    }
}

void Frac::setNewNum(int newNumer, int newDenom) {
    numer = newNumer;
    denom = newDenom;
    setSign();
    toShorten();
}

int Frac::intPart()
{
    if(numer < 0)
        return (numer - denom) / denom;
    else
        return numer / denom;
}

Frac Frac::fracPart()
{
    return Frac(intPart()) - *this;
}

double Frac::toDouble()
{
    return (double)numer / denom;
}

void Frac::print(FRAC_VISUAL regime)
{
    switch(regime) {
    case IMPROP:
        printf("(%i/%i)", numer, denom);
        break;
    case PROP:
        //printf("(%i|%i/%i)", intPart(), fracPart(), denom);
        break;
    }
}

int Frac::GCD(int a, int b) {
    return b ? GCD(b, a%b) : a;
}

int Frac::LCM(int a, int b) {
    return a * b / GCD(a, b);
}

void Frac::toShorten() {
    int k = GCD(numer, denom);
    numer /= k;
    denom /= k;
}

void Frac::setSign() {
    if(denom < 0) {
        numer *= -1;
        denom *= -1;
    }
}
