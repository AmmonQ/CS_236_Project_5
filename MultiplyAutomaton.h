//
// Created by aq229 on 9/7/21.
//

#ifndef CS_236_PROJECT_1_MULTIPLYAUTOMATON_H
#define CS_236_PROJECT_1_MULTIPLYAUTOMATON_H


#include "Automaton.h"

class MultiplyAutomaton : public Automaton {
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_MULTIPLYAUTOMATON_H
