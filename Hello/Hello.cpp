//
// Created by shah on 13/03/16.
//

#include "Hello.h"

std::string Hello::hello() {
    return "Hi";
}

void Hello::Sayhello() {
    std::cout<<hello()<<std::endl;
}