//
//  PostfixToInt.hpp
//  Практикум #1 "Калькулятор"
//
//  Created by Андрей Москалёв on 18/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#ifndef PostfixToInt_hpp
#define PostfixToInt_hpp

#include <stdio.h>
#include <cmath>
#include "Queue.hpp"
#include "Stack.hpp"
#include "Utils.hpp"
#include "Exceptions.hpp"
#include "CommonStructures.hpp"
#include "Math.hpp"
#include <QDebug>

double count_postfix_entry(Pair<Queue<std::string>, size_t> item, std::string var_index[] = {}, double var_value[] = {});

#endif /* PostfixToInt_hpp */
