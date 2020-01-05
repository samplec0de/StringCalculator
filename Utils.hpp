//
//  Utils.hpp
//  Практикум #1 "Калькулятор"
//
//  Created by Андрей Москалёв on 18/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include "Exceptions.hpp"

const int MAX_VARS_COUNT = int(1e5);
const double EULER = 2.71828182845904523536;
const double EPS = 1e-10;
//const double M_PI = 3.1415926535897932384;

bool is_operator(std::string c);
bool is_operand(char c);
bool is_integer_or_double(std::string s);
bool is_integer(std::string s);
bool starts_with(std::string s, std::string prefix);
bool is_open_brace(std::string c);
bool is_close_brace(std::string c);
bool is_triginometric(std::string c);
bool is_variable(std::string c);
bool is_pi(std::string c);
bool is_e(std::string c);
bool is_reserved(std::string c);
bool left_associative(std::string c);
int operator_priority(std::string op);
char opposite_brace(char);
std::string char_to_str(char);


#endif /* Utils_hpp */
