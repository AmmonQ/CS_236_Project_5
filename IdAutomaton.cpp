//
// Created by cppq on 9/8/2021.
//

#include "IdAutomaton.h"

// if character is a letter [A-Za-z]
void IdAutomaton::S0(const std::string &input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

// if character is a letter [A-Za-z] or number [0-9]
void IdAutomaton::S1(const std::string &input) {
    if (isalnum(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    // if not an alphanumeric char, it doesn't matter what comes next
    else {
        return;
    }
}