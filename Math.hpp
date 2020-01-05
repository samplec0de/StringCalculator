//
//  Math.hpp
//  Практикум #1 "Калькулятор"
//
//  Created by Андрей Москалёв on 03/10/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#ifndef Math_hpp
#define Math_hpp

#include <stdio.h>
#include "Utils.hpp"
#include "math.h"

const bool STEPAN = false;
const bool STEPAN_TRIGONOMA = false;

double mlog(double x, double y);
double mpow(double x, double y);
double mcos(double x);
double msin(double x);
double stdlog(double x, double y);

#endif /* Math_hpp */
