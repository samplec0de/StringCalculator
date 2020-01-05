//
//  Dijkstra.cpp
//  Алгоритм Дейкстры для перевода из инфиксной в постфиксную формы
//
//  Created by Андрей Москалёв on 18/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#include "Dijkstra.hpp"

void check_add_var_double(std::string &history, std::string &last_type, std::string var_index[], Queue<std::string> &answer, size_t &var_index_len) {
    if (history.size() != 0) {
        if (last_type == "var_double") {
            throw DijkstraValidateException("No operand between two operands");
        }
        if (last_type == "close_brace") {
            throw DijkstraValidateException("Variable or double after close brace");
        }
        if (last_type == "comma")
            last_type = "log_arg";
        else
            last_type = "var_double";
        // Если переменная
        if (!is_integer_or_double(history) && is_variable(history)) {
            bool set = false;
            for (size_t j = 0; j < var_index_len; ++j) {
                if (var_index[j] == history) {
                    set = true;
                    break;
                }
            }
            if (!set) {
                if (!is_pi(history) && !is_e(history)) {
                    var_index[var_index_len++] = history;
                    if (history[0] == '-') {
                        var_index[var_index_len - 1] = history.substr(1, history.size() - 1);
                    }
                }
            }
        }
        if (is_reserved(history)) {
            throw DijkstraValidateException("Variable name reserved");
        }
        answer.push(history);
//        if (VERBOSE >= 1) {
//            std::cerr << "answer.push(" << history << ")\n";
//        }
        history = "";
    }
}

Pair<Queue<std::string>, size_t> convert(std::string s, std::string var_index[], int VERBOSE) {
    s += ' ';
    Queue<std::string> answer;
    Stack<std::string> st;
    Stack<char> braces;
    std::string history = "";
    int last_char = 0;
    size_t var_index_len = 0;
    std::string last_type = "";
    if (s.size() == 0) {
        throw DijkstraValidateException("Empty one");
    }
    std::string str_first_char = char_to_str(s[0]);
    if (!is_variable(str_first_char) && !is_integer_or_double(str_first_char) && !is_open_brace(str_first_char) && s[0] != '-' && s[0] != '+') {
        throw DijkstraValidateException("Expression begins from illegal char");
    }
    for (int i = 0; i < s.size(); ++i) {
        std::string c = char_to_str(s[i]);
        if (c == "e" && history.size() > 0 && is_integer_or_double(history)) {
            if (history.find('e') != -1) {
                throw DijkstraValidateException("Wrong double format");
            }
            history += c;
            last_char = i;
            continue;
        }
        if (c == " ") {
            check_add_var_double(history, last_type, var_index, answer, var_index_len);
            continue;
        }
        if ((c == "-" || c == "+") && (i == 0 || is_operator(char_to_str(s[last_char])) || is_open_brace(char_to_str(s[last_char])) || s[last_char] == ',')) {
//            if (last_type == "unar_plus") {
//                throw DijkstraValidateException("Double unar minus");
//            }
            last_type = "unar_plus";
            if (history.size() != 0) {
                throw DijkstraValidateException("Unar minus after variable or double");
            }
            if (c == "-") {
                st.push("-u");
                last_type = "unar_minus";
            }
            continue;
        }
        last_char = i;
        bool input_operand = is_operand(c[0]);
        bool input_operator = is_operator(c);
        if (c == ".") {
            last_type = "point";
            if (i == s.size() - 2) {
                throw DijkstraValidateException("Point on the end of the string");
            }
            if (!(s[i + 1] >= '0' && s[i + 1] <= '9')) {
                throw DijkstraValidateException("Illegal char after point");
            }
            if (history.size() == 0) {
                history = "0.";
            }
            else {
                if (is_integer(history)) {
                    history += '.';
                }
                else {
                    throw DijkstraValidateException("Point not allowed");
                }
            }
            continue;
        }
//        Встретился sin/cos
        if (i + 2 < s.size() && (s.substr(i, 3) == "sin" || s.substr(i, 3) == "cos")) {
            if (history.size() > 0 && !(history.size() > 2 && is_triginometric(history.substr(history.size() - 3, 3)))) {
                if (i + 3 < s.size() && is_open_brace(char_to_str(s[i + 3]))) {
                    throw DijkstraValidateException("Variable or double before sin/cos");
                }
            }
            if (i + 3 < s.size() && is_open_brace(char_to_str(s[i + 3]))) {
                if (history.size() > 0) {
                    throw DijkstraValidateException("Variable or double before sin/cos");
                }
                c = s.substr(i, 3);
                braces.push(s[i + 3]);
                i = i + 3;
                st.push(c);
                last_type = "trigonometric";
                last_char = i;
                continue;
            }
            else if (i + 3 < s.size() && s[i + 3] != '_' && !(tolower(s[i + 3]) >= 'a' && tolower(s[i + 3]) <= 'z') && !(s[i + 3] >= '0' && s[i + 3] <= '9') && s[i + 3] != ' ' && !is_operator(char_to_str(s[i + 3]))) {
                    throw DijkstraValidateException("Bad char after sin/cos");
            }
        }
//        Встретился log
        if (i + 2 < s.size() && s.substr(i, 3) == "log") {
            if (history.size() > 0 && !(history.size() > 2 && is_triginometric(history.substr(history.size() - 3, 3)))) {
                if (i + 3 < s.size() && is_open_brace(char_to_str(s[i + 3]))) {
                    throw DijkstraValidateException("Variable or double before log");
                }
            }
            if (i + 3 < s.size() && is_open_brace(char_to_str(s[i + 3]))) {
                if (history.size() > 0) {
                    throw DijkstraValidateException("Variable or double before log");
                }
                braces.push(s[i + 3]);
                braces.push('@');
                i = i + 3;
                st.push("log");
                st.push("@");
                last_type = "log";
                last_char = i;
                continue;
            }
            else if (i + 3 < s.size() && s[i + 3] != '_' && !(tolower(s[i + 3]) >= 'a' && tolower(s[i + 3]) <= 'z') && !(s[i + 3] >= '0' && s[i + 3] <= '9') && s[i + 3] != ' ' && !is_operator(char_to_str(s[i + 3]))) {
                    throw DijkstraValidateException("Bad char after log");
            }
        }
        
        if (input_operand) {
//            last_type = "var_double";
            history += c;
            if (s[i + 1] != ' ' && !(s[i + 1] >= '0' && s[i + 1] <= '9') && s[i + 1] != '.' && !is_close_brace(char_to_str(s[i + 1])) && !is_operator(char_to_str(s[i + 1])) && !(tolower(s[i + 1]) >= 'a' && tolower(s[i + 1]) <= 'z')) {
                std::cout << s[i + 1] << "\n";
                throw DijkstraValidateException("Illegal char after digit");
            }
        }
        else if (not input_operator && not input_operand && !is_open_brace(c) && !is_close_brace(c)) {
//         Что-то плохое нам дали (!)
            if (is_integer_or_double(history)) {
                throw DijkstraValidateException("Uknown data");
            }
//            Дописываем
            history += c;
        }
//        Если прочитан операнд (число/переменная), записать его в выходную последовательность.
        else if (c != "," && not input_operand && history.size() != 0 && !input_operator) {
            if (last_type == "var_double") {
                throw DijkstraValidateException("No operand between two operands");
            }
            if (last_type == "close_brace") {
                throw DijkstraValidateException("Variable or double after close brace");
            }
            last_type = "var_double";
//            check_add_var_double(history, last_type, var_index, answer, var_index_len);
            // Если переменная
            if (!is_integer_or_double(history) && is_variable(history)) {
                bool set = false;
                for (size_t j = 0; j < var_index_len; ++j) {
                    if (var_index[j] == history) {
                        set = true;
                        break;
                    }
                }
                if (!set) {
                    if (!is_pi(history) && !is_e(history)) {
                        var_index[var_index_len++] = history;
                        if (history[0] == '-') {
                            var_index[var_index_len - 1] = history.substr(1, history.size() - 1);
                        }
                    }
                }
            }
            if (is_reserved(history)) {
                throw DijkstraValidateException("Variable name reserved");
            }
            answer.push(history);
            if (VERBOSE >= 1)
                std::cerr << "answer.push(" << history << ")\n";
            history = "";
        }
//        Если прочитан знак операции, вытолкнуть из стека в выходную последовательность все операции с большим либо равным приоритетом, а прочитанную операцию положить в стек.
        if (input_operator) {
            if (last_type != "" && last_type != "close_brace" && last_type != "var_double" && last_type != "unar_minus" && history.size() == 0 && last_type != "trigonometric" && last_type != "comma") {
                throw DijkstraValidateException("Operator not after close brace, variable, double or unar minus");
            }
            if (is_integer_or_double(history.substr(0, history.size() - 1)) && history.back() == 'e') {
                history += '-';
                last_char = i;
                continue;
            }
            check_add_var_double(history, last_type, var_index, answer, var_index_len);
            last_type = "operator";
            while (!st.is_empty() && ((left_associative(c) && operator_priority(st.top()) >= operator_priority(c)) || (!left_associative(c) && operator_priority(st.top()) > operator_priority(c)))) {
                answer.push(st.top());
                if (VERBOSE >= 1) {
                    std::cerr << "answer.push(" << st.top() << ")\n";
                    std::cerr << "st.pop()\n";
                }
                st.pop();
            }
            std::string tmp = "";
            tmp += c;
            st.push(tmp);
            if (VERBOSE >= 1) {
                std::cerr << "st.push(" << tmp << ")\n";
            }
        }
//        Если прочитана открывающая скобка, положить ее в стек.
        else if (is_open_brace(c)) {
            if (last_type != "" && last_type != "operator" && last_type != "open_brace" && last_type != "trigonometric" && last_type != "unar_minus" && last_type != "comma") {
                throw DijkstraValidateException("Brace not after operator or begin");
            }
            last_type = "open_brace";
            if (history.size() != 0) {
                throw DijkstraValidateException("Open brace after variable or double");
            }
            st.push(c);
            braces.push(c[0]);
            if (VERBOSE >= 1) {
                std::cerr << "st.push(\"" + c + "\")\n";
            }
        }
//        Если прочитана закрывающая скобка, вытолкнуть из стека в выходную последовательность все до открывающей скобки. Сами скобки уничтожаются.
        else if (is_close_brace(c)) {
            check_add_var_double(history, last_type, var_index, answer, var_index_len);
            if (last_type != "var_double" && last_type != "close_brace" && last_type != "log_arg") {
                throw DijkstraValidateException("Close brace not after variable or double");
            }
            if (c == ",")
                last_type = "comma";
            else
                last_type = "close_brace";
            if (braces.is_empty()) {
                throw DijkstraValidateException("No open brace found");
            }
            if (braces.top() != opposite_brace(c[0]) && braces.top() != '@') {
                throw DijkstraValidateException("Close brace is not opposite to last open brace");
            }
            braces.pop();
            while (!st.is_empty() && !is_open_brace(st.top()) && !is_triginometric(st.top()) && st.top() != "log") {
                std::string top = st.top();
                answer.push(top);
                if (VERBOSE >= 1) {
                    std::cerr << "answer.push(" << st.top() << ") - \")\"\n";
                    std::cerr << "st.pop()\n";
                }
                st.pop();
            }
            if (st.is_empty()) {
                throw DijkstraValidateException("Brace, trigonometric or log not found");
            }
            if (is_triginometric(st.top())) {
                answer.push(st.top());
            }
            else if (st.top() == "log") {
                answer.push("log");
            }
            st.pop();
            if (VERBOSE >= 1) {
                std::cerr << "st.pop()\n";
            }
        }
        else {
//            wtf fix me
        }
    }
    while (!st.is_empty()) {
        if (st.top() != "(" || st.top() != "[") {
            // Если тригонома, проталкиваем без скобки
            if (starts_with(st.top(), "sin") || starts_with(st.top(), "cos")) {\
                if (braces.top() != opposite_brace(st.top().back())) {
                    throw DijkstraValidateException("Close brace is not opposite to last open brace");
                }
                answer.push(st.top().substr(1, st.top().size() - 1));
                if (VERBOSE >= 1) {
                    std::cerr << "answer.push(" << st.top() << ") - \")\"\n";
                }
                st.pop();
                if (VERBOSE >= 1) {
                    std::cerr << "st.pop()\n";
                }
                continue;
            }
        }
        else if (braces.top() != opposite_brace(st.top()[0])) {
            throw DijkstraValidateException("Close brace is not opposite to last open brace");
        }
        answer.push(st.top());
        if (VERBOSE >= 1) {
            std::cerr << "answer.push(" << st.top() << ") - \")\"\n";
        }
        st.pop();
        if (VERBOSE >= 1) {
            std::cerr << "st.pop()\n";
        }
    }
    if (!braces.is_empty()) {
        throw DijkstraValidateException("Wrong brace balance");
    }
    if (last_type != "close_brace" && last_type != "var_double") {
        throw DijkstraValidateException("Unexpected EOF");
    }
    return Pair<Queue<std::string>, size_t>(answer, var_index_len);
}
