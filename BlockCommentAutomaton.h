//
// Created by cppq on 9/8/2021.
//

#ifndef CS_236_PROJECT_1_BLOCKCOMMENTAUTOMATON_H
#define CS_236_PROJECT_1_BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton {
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
public:
    BlockCommentAutomaton() : Automaton(TokenType::COMMENT) {}

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_BLOCKCOMMENTAUTOMATON_H
