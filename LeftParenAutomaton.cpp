//
// Created by aq229 on 9/7/21.
//

#include "LeftParenAutomaton.h"

void LeftParenAutomaton::S0(const std::string &input) {
    if (input[index] == '(') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}