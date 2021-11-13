//
// Created by aq229 on 9/7/21.
//

#include "RightParenAutomaton.h"

void RightParenAutomaton::S0(const std::string &input) {
    if (input[index] == ')') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}