//
// Created by cppq on 9/9/2021.
//

#include "UndefinedStringAutomaton.h"

void UndefinedStringAutomaton::S0(const std::string &input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
}

void UndefinedStringAutomaton::S1(const std::string &input) {
    // if it's out of bounds
    if (inputRead >= (int)input.size()) {
        return;
    }
    // if it is a single quote (it may result in an end of string or another
    // single quote
    else if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        if (input[index] == '\n') {
            newLines++;
        }
        inputRead++;
        index++;
        S1(input);
    }
}

void UndefinedStringAutomaton::S2(const std::string &input) {
    // if there is another single quote it is a valid set of characters
    // if there is a space afterwards, the string would be done
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}