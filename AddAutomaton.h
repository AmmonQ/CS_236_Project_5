//
// Created by aq229 on 9/7/21.
//

#ifndef CS_236_PROJECT_1_ADDAUTOMATON_H
#define CS_236_PROJECT_1_ADDAUTOMATON_H


#include "Automaton.h"

class AddAutomaton : public Automaton{
public:
    AddAutomaton() : Automaton(TokenType::ADD) {}

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_ADDAUTOMATON_H
