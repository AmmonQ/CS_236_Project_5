//
// Created by cppq on 10/11/2021.
//

#ifndef CS_236_PROJECT_3_INTERPRETER_H
#define CS_236_PROJECT_3_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Tuple.h"
#include <algorithm>

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
public:
    Interpreter(DatalogProgram datalogProgram1);
    DatalogProgram getDatalogProgram();
    void setDatalogProgram(DatalogProgram newDatalogProgram);
    Database getDatabase();
    void setDatabase(const Database& newDatabase);

    // for evaluating queries
    Relation evaluatePredicate(Predicate p);
    Relation evaluateRule(Rule r, Predicate scheme);
    void evaluateAllQueries();
    void evaluateAllRules();

    void evaluateAllRulesSCCs(vector<map<int, set<int>>> allSCCs);
    void evaluateRulesSCCs(vector<map<int, set<int>>> allSCCs);

    Rule getRuleFromNumber(int number);
};


#endif //CS_236_PROJECT_3_INTERPRETER_H
