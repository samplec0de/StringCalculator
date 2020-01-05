//
//  Utils.cpp
//  Практикум #1 "Калькулятор"
//
//  Created by Андрей Москалёв on 18/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#include "Utils.hpp"

bool is_operator(std::string c) {
    std::string operands[] = {"+", "-", "/", "*", "^", "sin", "cos", "-u", "log"};
    for (std::string operand : operands) {
        if (operand == c) {
            return true;
        }
    }
    return false;
}

bool is_operand(char c) {
    return c >= '0' && c <= '9';
}

int operator_priority(std::string op) {
    if (op == "+" || op == "-") {
        return 1;
    }
    if (op == "/" || op == "*") {
        return 2;
    }
    if (op == "-u") {
        return 47;
    }
    if (op == "^") {
        return 48;
    }
    if (op == "(") {
        return 0;
    }
    if (op == "log") {
        return 0;
    }
    if (op == "sin" || op == "cos") {
        return 0;
    }
    if (op == "@") {
        return 0;
    }
    std::cerr << op << '\n';
    throw DijkstraException("operator priority not set");
    return -1;
}

bool is_integer_or_double(std::string s) {
    if (s.size() == 0 || s.back() < '0' || s.back() > '9')
        return false;
//    int point = -1;
//    int start = 0;
//    if (s[0] == '-' || s[0] == '+') {
//        ++start;
//    }
//    if (start == 1 && s.size() == 1)
//        return false;
//    for (int i = start; i < s.size(); ++i) {
//        if (s[i] == '.') {
//            if (point == -1)
//                point = i;
//            else
//                return false;
//        }
//        else if (!(s[i] >= '0' && s[i] <= '9')) {
//            return false;
//        }
//    }
    try {
        std::stod(s);
    } catch (std::invalid_argument e) {
        return false;
    } catch (std::out_of_range e) {
        throw MathException("Out of double range");
    }
    return true;
}

bool is_integer(std::string s) {
    for (char c : s) {
        if (!(c >= '0' && c <= '9'))
            return false;
    }
    return true;
}

bool starts_with(std::string s, std::string prefix) {
    return s.substr(0, prefix.size()) == prefix;
}

std::string char_to_str(char c) {
    std::string ans = "";
    ans += c;
    return ans;
}

char opposite_brace(char c) {
    if (c == '[') {
        return ']';
    }
    if (c == '(') {
        return ')';
    }
    if (c == ')') {
        return '(';
    }
    if (c == ']') {
        return '[';
    }
    if (c == ',') {
        return '(';
    }
    
    std::cerr << c << '\n';
    throw UtilsException("Uknown brace type");
    return '#';
}

bool is_open_brace(std::string c) {
    return c == "(" || c == "[" || c == "@";
}

bool is_close_brace(std::string c) {
    return c == ")" || c == "]" || c == ",";
}

bool is_triginometric(std::string c) {
    return c == "sin" || c == "cos";
}

bool is_variable(std::string c) {
    if (is_integer_or_double(c) || is_operator(c) || is_open_brace(c) || is_close_brace(c)) {
        return false;
    }
    std::string can_starts_from = "abcdefghijklmnopqrstuvwxyz_";
    int ind = 0;
//    if (c[ind] == '-') {
//        ++ind;
//    }
    if (ind < c.size() &&  can_starts_from.find(tolower(tolower(c[ind]))) == -1) {
        throw DijkstraValidateException("Something variable-like, but starts not from alpha");
        return false;
    }
    std::string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz_";
    for (int i = ind; i < c.size(); ++i) {
        if (alphabet.find(tolower(c[i])) == -1) {
            throw DijkstraValidateException("Something variable-like, but contains illegal char");
            return false;
        }
    }
    return true;
}

bool is_pi(std::string c) {
    std::string pi[] = {"pi", "PI", "M_PI", "m_pi"};
    for (std::string now : pi) {
        if (now == c) {
            return true;
        }
    }
    return false;
}

bool is_e(std::string c) {
    std::string e[] = {"e", "E"};
    for (std::string now : e) {
        if (now == c) {
            return true;
        }
    }
    return false;
}

bool is_reserved(std::string c) {
    std::string reserved[] = {"sin", "cos", "log"};
    for (std::string now : reserved) {
        if (now == c) {
            return true;
        }
    }
    return false;
}

bool left_associative(std::string c) {
    return c != "^";
}
