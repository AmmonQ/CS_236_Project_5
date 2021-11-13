//
// Created by cppq on 9/23/2021.
//

#ifndef CS_236_PROJECT_2_DATALOGPROGRAM_H
#define CS_236_PROJECT_2_DATALOGPROGRAM_H

#include <vector>
#include <string>
#include "Rule.h"
#include "Predicate.h"
#include <set>

using namespace std;

class DatalogProgram {
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
public:
    DatalogProgram();
    DatalogProgram(vector<Predicate> schemes, vector<Predicate> facts, vector<Rule> rules, vector<Predicate> queries);
    string toString();
    vector<Predicate> getSchemes();
    vector<Predicate> getFacts();
    vector<Rule> getRules();
    vector<Predicate> getQueries();
    Predicate getScheme(int index);
    Predicate getFact(int index);
    Rule getRule(int index);
    Predicate getQuery(int index);
    int getSchemesSize();
    int getFactsSize();
    int getRulesSize();
    int getQueriesSize();
};


#endif //CS_236_PROJECT_2_DATALOGPROGRAM_H
