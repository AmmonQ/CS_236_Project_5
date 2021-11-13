//
// Created by cppq on 9/9/2021.
//

#ifndef CS_236_PROJECT_1_UNDEFINEDBLOCKCOMMENTAUTOMATON_H
#define CS_236_PROJECT_1_UNDEFINEDBLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class UndefinedBlockCommentAutomaton : public Automaton {
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
public:
    UndefinedBlockCommentAutomaton() : Automaton(TokenType::UNDEFINED) {}

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_UNDEFINEDBLOCKCOMMENTAUTOMATON_H
