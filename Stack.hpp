//
//  Stack.hpp
//  Алгоритм Дейкстры для перевода из инфиксной в постфиксную формы
//
//  Created by Андрей Москалёв on 18/09/2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>
#include <string>

template <class T>
struct Stack {
    struct Node {
        T elem;
        Node * next;
        Node() {
            next = nullptr;
        }
    };
    Node * L;
    size_t size;
    Stack() {
        this->size = 0;
        this->L = nullptr;
    }
    void push(T x) {
        ++size;
        if (this->L == nullptr) {
            L = new Node;
            L->elem = x;
            return;
        }
        Node * tmp = new Node;
        tmp->elem = L->elem;
        tmp->next = L->next;
        L->next = tmp;
        L->elem = x;
    }
    void pop() {
        if (L->next == nullptr) {
            delete L;
            L = nullptr;
            --size;
            return;
        }
        L->elem = L->next->elem;
        Node * tmp = L->next;
        L->next = tmp->next;
        delete tmp;
        --size;
    }
    T top() {
        return L->elem;
    }
    bool is_empty() {
        return this->L == nullptr;
    }
    void clear() {
        while (!this->is_empty()) {
            this->pop();
        }
    }
};

#endif /* Stack_hpp */
