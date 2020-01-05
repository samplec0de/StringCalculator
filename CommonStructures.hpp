//
//  CommonStructures.hpp
//  Практикум #1 "Калькулятор"
//
//  Created by Андрей Москалёв on 26/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#ifndef CommonStructures_hpp
#define CommonStructures_hpp

#include <stdio.h>

template <class T, class T2>
struct Pair {
    T first;
    T2 second;
    Pair() {
        
    }
    Pair(T first, T2 second) {
        this->first = first;
        this->second = second;
    }
};

template <class T, class T2, class T3>
struct Tuple {
    T first;
    T2 second;
    T3 third;
    Tuple() {
        
    }
    Tuple(T first, T2 second, T3 third) {
        this->first = first;
        this->second = second;
        this->third = third;
    }
};

#endif /* CommonStructures_hpp */
