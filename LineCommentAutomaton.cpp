//
// Created by cppq on 9/8/2021.
//

#include "LineCommentAutomaton.h"

void LineCommentAutomaton::S0(const std::string &input) {

    if (index + 1 < input.size() && input[index] == '#' && input[index + 1] == '|') {
        Serr();
    }
    else if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void LineCommentAutomaton::S1(const std::string &input) {
    // if end of file or out of bounds
    if (input[index] == '\n' || index >= input.size()) {
        return;
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}