//
// Created by cppq on 9/8/2021.
//

#ifndef CS_236_PROJECT_1_LINECOMMENTAUTOMATON_H
#define CS_236_PROJECT_1_LINECOMMENTAUTOMATON_H

#include "Automaton.h"

class LineCommentAutomaton : public Automaton {
private:
    void S1(const std::string& input);
public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_LINECOMMENTAUTOMATON_H
