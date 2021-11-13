//
// Created by aq229 on 9/7/21.
//

#ifndef CS_236_PROJECT_1_QMARKAUTOMATON_H
#define CS_236_PROJECT_1_QMARKAUTOMATON_H

#include "Automaton.h"

class QMarkAutomaton : public Automaton {
public:
    QMarkAutomaton() : Automaton(TokenType::Q_MARK) {};

    void S0(const std::string& input);
};


#endif //CS_236_PROJECT_1_QMARKAUTOMATON_H
