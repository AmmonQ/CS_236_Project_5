//
// Created by cppq on 9/9/2021.
//

#include "UndefinedBlockCommentAutomaton.h"

void UndefinedBlockCommentAutomaton::S0(const std::string &input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void UndefinedBlockCommentAutomaton::S1(const std::string &input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void UndefinedBlockCommentAutomaton::S2(const std::string &input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if (index >= input.size()) {
        return;
    }
    else if (input[index] == '\n') {
        inputRead++;
        index++;
        newLines++;
        S2(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void UndefinedBlockCommentAutomaton::S3(const std::string &input) {
    if (input[index] == '#') {
        Serr();
    }
    else if (input[index] == '\n') {
        inputRead++;
        index++;
        newLines++;
        S2(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}