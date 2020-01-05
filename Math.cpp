//
//  Math.cpp
//  Практикум #1 "Калькулятор"
//
//  Created by Андрей Москалёв on 03/10/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#include "Math.hpp"

double mpow(double x, double y);


double bpow(double a, int n) {
    double res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            --n;
        }
        else {
            a *= a;
            n >>= 1;
        }
    }
    return res;
}

double factorial(int n) {
    double a = 1;
    for (int p = 1; p <= n; ++p) {
        a = a * p;
    }
    return a;
}

double exp(double x) {
    double s = 0;
    int a = 0, b = 0;
    double d = 2 + EPS;
    while (d - s > EPS || s - d > EPS) {
        d = s;
        s = s + (bpow(x, a)) / (double(factorial(a)));
        ++a;
        ++b;
    }
    return s;
}

double mln(double x) {
    double count = 1, totalValue = 0, z, powe = 1, y, lst=1;
    z = (x + 1) / (x - 1);
    double step = ((x - 1) * (x - 1)) / ((x + 1) * (x + 1));
    while (totalValue - lst > EPS || totalValue - lst < -EPS) {
        z *= step;
        y = (1 / powe) * z;
        lst=totalValue;
        totalValue = totalValue + y;
        powe = powe + 2;
        count++;
    }
    return 2 * totalValue;
}

double mpow(double x, double y) {
    if (!STEPAN)
        return pow(x, y);
    return exp(y * mln(x));
}


double mlog(double x, double y) {
    if (!STEPAN)
        return stdlog(x, y);
    return mln(y) / mln(x);
}

double stdlog(double x, double y) {
    return log(y) / log(x);
}

double msin(double x) {
    if (!STEPAN_TRIGONOMA) {
        return sin(x);
    }
    x = fmod(x, 2 * M_PI);
    double sine = 0;
    int a = 1, b = 1;
    double dsin= 2 + EPS;
    while (dsin - sine > EPS || sine - dsin > EPS) {
        dsin = sine;
        sine = sine + (bpow(-1, b + 1)) * (bpow(x, a)) / (double(factorial(a)));
        a += 2;
        ++b;
    }
    return sine;
}

double mcos(double x) {
    if (!STEPAN_TRIGONOMA) {
        return cos(x);
    }
    x = fmod(x, 2 * M_PI);
    double sine = 0;
    int a = 0, b = 0;
    double dsin = 2 + EPS;
    while (dsin - sine > EPS || sine - dsin > EPS) {
        dsin = sine;
        sine = sine + (bpow(-1, b + 1)) * (bpow(x, a)) / (double(factorial(a)));
        a += 2;
        ++b;
    }
    return -sine;
}
