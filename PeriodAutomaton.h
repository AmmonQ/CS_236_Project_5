//
// Created by aq229 on 9/7/21.
//

#ifndef CS_236_PROJECT_1_PERIODAUTOMATON_H
#define CS_236_PROJECT_1_PERIODAUTOMATON_H

#include "Automaton.h"

class PeriodAutomaton : public Automaton {
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_PERIODAUTOMATON_H
