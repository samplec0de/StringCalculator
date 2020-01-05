//
//  Dijkstra.hpp
//  Алгоритм Дейкстры для перевода из инфиксной в постфиксную формы
//
//  Created by Андрей Москалёв on 18/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#ifndef Dijkstra_hpp
#define Dijkstra_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"
#include "CommonStructures.hpp"

Pair<Queue<std::string>, size_t> convert(std::string s, std::string var_index[] = {}, int VERBOSE = 0);

#endif /* Dijkstra_hpp */
