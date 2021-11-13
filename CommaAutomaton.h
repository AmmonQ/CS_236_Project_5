//
// Created by aq229 on 9/7/21.
//

#ifndef CS_236_PROJECT_1_COMMAAUTOMATON_H
#define CS_236_PROJECT_1_COMMAAUTOMATON_H

#include "Automaton.h"

class CommaAutomaton : public Automaton {
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {};

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_COMMAAUTOMATON_H
