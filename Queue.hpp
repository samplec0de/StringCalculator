//
//  Queue.hpp
//  Алгоритм Дейкстры для перевода из инфиксной в постфиксную формы
//
//  Created by Андрей Москалёв on 18/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include <string>

template <class T>
struct Queue {
    bool empty;
    
    struct Node {
        T elem;
        Node * next;
        Node() {
            next = nullptr;
        }
    };
    Node * L, * R;
    size_t size;
    Queue() {
        size = 0;
        empty = true;
        L = new Node;
        R = L;
    }
    void push(T x) {
        ++size;
        if (empty) {
            L->elem = x;
            empty = false;
            return;
        }
        Node * tmp = new Node;
        tmp->elem = x;
        R->next = tmp;
        R = R->next;
    }
    void pop() {
        if (L->next == nullptr) {
            empty = true;
            --size;
            R = L;
            return;
        }
        Node * tmp = L;
        L = L->next;
        delete tmp;
        --size;
    }
    T front() {
        return L->elem;
    }
    bool is_empty() {
        return empty;
    }
    void clear() {
        while (!is_empty()) {
            pop();
        }
    }
};


#endif /* Queue_hpp */
