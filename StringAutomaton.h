//
// Created by cppq on 9/8/2021.
//

#ifndef CS_236_PROJECT_1_STRINGAUTOMATON_H
#define CS_236_PROJECT_1_STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton {
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
public:
    StringAutomaton() : Automaton(TokenType::STRING) {}

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_STRINGAUTOMATON_H
