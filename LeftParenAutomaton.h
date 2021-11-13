//
// Created by aq229 on 9/7/21.
//

#ifndef CS_236_PROJECT_1_LEFTPARENAUTOMATON_H
#define CS_236_PROJECT_1_LEFTPARENAUTOMATON_H

#include "Automaton.h"

class LeftParenAutomaton : public Automaton {
public:
    LeftParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_LEFTPARENAUTOMATON_H
