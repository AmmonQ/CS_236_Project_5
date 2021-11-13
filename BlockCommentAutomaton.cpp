//
// Created by cppq on 9/8/2021.
//

#include "BlockCommentAutomaton.h"

void BlockCommentAutomaton::S0(const std::string &input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S1(const std::string &input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S2(const std::string &input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if (index >= input.size()) {
        Serr();
    }
    // valid character but not end of block comment
    else {
        if (input[index] == '\n') {
            newLines++;
        }
        inputRead++;
        index++;
        S2(input);
    }
}

void BlockCommentAutomaton::S3(const std::string &input) {
    if (input[index] == '#') {
        inputRead++;
    }
    else if (input[index] == '\n') {
        inputRead++;
        index++;
        newLines++;
        S3(input);
    }
    else if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}