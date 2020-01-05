//
//  Exceptions.hpp
//  Подсчет значения ПОЛИЗ
//
//  Created by Андрей Москалёв on 18/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#ifndef Exceptions_hpp
#define Exceptions_hpp

#include <stdio.h>
#include <string>

struct UknownBinaryOperationException {
    std::string meta;
    UknownBinaryOperationException() {
        this->meta = "not defined";
    }
    UknownBinaryOperationException(std::string reason) {
        this->meta = reason;
    }
    std::string reason() const throw () {
        return "Uknown binary operation: " + meta + "\n";
    }
};

struct DijkstraException {
    std::string meta;
    DijkstraException() {
        this->meta = "not defined";
    }
    DijkstraException(std::string reason) {
        this->meta = reason;
    }
    std::string reason() const throw () {
        return "Error in Dijkstra: " + meta + "\n";
    }
};

struct DijkstraValidateException {
    std::string meta;
    DijkstraValidateException() {
        this->meta = "not defined";
    }
    DijkstraValidateException(std::string reason) {
        this->meta = reason;
    }
    std::string reason() const throw () {
        return "Error in Dijkstra validator: " + meta + "\n";
    }
};

struct UtilsException {
    std::string meta;
    UtilsException() {
        this->meta = "not defined";
    }
    UtilsException(std::string reason) {
        this->meta = reason;
    }
    std::string reason() const throw () {
        return "Error in utils function: " + meta + "\n";
    }
};

struct MathException {
    std::string meta;
    MathException() {
        this->meta = "not defined";
    }
    MathException(std::string reason) {
        this->meta = reason;
    }
    std::string reason() const throw () {
        return "Error in utils function: " + meta + "\n";
    }
};

#endif /* Exceptions_hpp */
