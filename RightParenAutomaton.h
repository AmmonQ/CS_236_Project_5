//
// Created by aq229 on 9/7/21.
//

#ifndef CS_236_PROJECT_1_RIGHTPARENAUTOMATON_H
#define CS_236_PROJECT_1_RIGHTPARENAUTOMATON_H

#include "Automaton.h"

class RightParenAutomaton : public Automaton {
public:
    RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_RIGHTPARENAUTOMATON_H
