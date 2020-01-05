//
//  PostfixToInt.cpp
//  Практикум #1 "Калькулятор"
//
//  Created by Андрей Москалёв on 18/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#include "PostfixToInt.hpp"

double get_variable_value(std::string key, size_t var_count, std::string var_index[], double var_value[]) {
    if (key == "nan")
        return std::stod("nan");
    if (key == "inf")
        return std::stod("inf");
    if (key == "-nan")
        return std::stod("-nan");
    if (key == "-inf")
        return std::stod("-inf");
    int minus = 1;
    if (key[0] == '-') {
        minus = -1;
        key = key.substr(1, key.size() - 1);
    }
    if (is_pi(key)) {
        return M_PI * minus;
    }
    if (is_e(key)) {
        return EULER * minus;
    }
    for (size_t i = 0; i < var_count; ++i) {
        if (var_index[i] == key) {
            return var_value[i] * minus;
        }
    }
    throw MathException("Variable value not found");
}

double count_postfix_entry(Pair<Queue<std::string>, size_t> item, std::string var_index[], double var_value[]) {
    Stack<std::string> st;
    Queue<std::string> q = item.first;
    size_t var_count = item.second;
    while (!q.is_empty()) {
        std::string cur = q.front();
        q.pop();
        if (is_integer_or_double(cur) || is_variable(cur)) {
            st.push(cur);
        }
        else if (is_operator(cur)) {
            if (cur == "+" || cur == "-" || cur == "/" || cur == "*" || cur == "^" || cur == "log") {
                if (st.is_empty()) {
                    throw MathException("Dominating operands");
                }
                std::string a = st.top();
                st.pop();
                if (st.is_empty()) {
                    throw MathException("Dominating operands");
                }
                std::string b = st.top();
                st.pop();
                double a_d = 0, b_d = 0;
                if (is_integer_or_double(a)) {
                    a_d = stod(a);
                }
                else {
                    a_d = get_variable_value(a, var_count, var_index, var_value);
                    
                }
                if (is_integer_or_double(b)) {
                    b_d = stod(b);
                }
                else {
                    b_d = get_variable_value(b, var_count, var_index, var_value);
                }
                switch (cur[0]) {
                    case '+':
                        st.push(std::to_string(a_d + b_d));
                        break;
                        
                    case '-':
                        st.push(std::to_string(b_d - a_d));
                        break;
                    
                    case '/':
                        if (fabs(a_d) <= EPS) {
                            throw MathException("Division by zero");
                        }
                        st.push(std::to_string(b_d / a_d));
                        break;
                    
                    case '*':
                        st.push(std::to_string(a_d * b_d));
                        break;
                    case '^':
                        st.push(std::to_string(mpow(b_d, a_d)));
                        break;
                    case 'l':
                        if (b_d <= EPS) {
                            throw MathException("The base of the logarithm is less than 0");
                        }
                        if (fabs(b_d - 1) <= EPS) {
                            throw MathException("The base of the logarithm is equal to 1");
                        }
                        st.push(std::to_string(mlog(b_d, a_d)));
                        break;
                    default:
                        break;
                }
            }
            else if (cur == "cos") {
                if (st.is_empty()) {
                    throw MathException("Dominating operators");
                }
                std::string a = st.top();
                st.pop();
                double a_d = 0.0;
                if (is_integer_or_double(a)) {
                    a_d = stod(a);
                }
                else {
                    a_d = get_variable_value(a, var_count, var_index, var_value);
                }
                st.push(std::to_string(mcos(a_d)));
            }
            else if (cur == "sin") {
                if (st.is_empty()) {
                    throw MathException("Dominating operators");
                }
                std::string a = st.top();
                st.pop();
                double a_d = 0.0;
                if (is_integer_or_double(a)) {
                    a_d = stod(a);
                }
                else {
                    a_d = get_variable_value(a, var_count, var_index, var_value);
                }
                st.push(std::to_string(msin(a_d)));
            }
            else if (cur == "-u") {
                if (st.is_empty()) {
                    throw MathException("Dominating operators");
                }
                std::string a = st.top();
                st.pop();
                double a_d = 0.0;
                if (is_integer_or_double(a)) {
                    a_d = stod(a);
                }
                else {
                    a_d = get_variable_value(a, var_count, var_index, var_value);
                }
                st.push(std::to_string(-a_d));
            }
        }
    }
    if (st.is_empty()) {
        throw MathException("Dominating operands");
    }
    double ans = 0;
    if (!is_integer_or_double(st.top()) && !is_variable(st.top())) {
        throw MathException("Calculation error");
    }
    else if (is_variable(st.top())) {
        ans = get_variable_value(st.top(), var_count, var_index, var_value);
//        qDebug() << QString::fromStdString(st.top());
//        qDebug() << QString::fromStdString(var_index[0]);
//        qDebug() << QString::fromStdString(std::to_string(var_value[0]));
//        qDebug() << QString::fromStdString(std::to_string(var_value[1]));
    }
    else {
        ans = stod(st.top());
    }
    st.pop();
    if (!st.is_empty()) {
        throw MathException("Dominating operands");
    }
    qDebug() << ans;
    return ans;
}
