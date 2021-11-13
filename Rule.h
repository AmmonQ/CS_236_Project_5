//
// Created by cppq on 9/23/2021.
//

#ifndef CS_236_PROJECT_2_RULE_H
#define CS_236_PROJECT_2_RULE_H

#include "Predicate.h"
#include <vector>
#include <string>

using namespace std;

class Rule {
private:
    vector<Predicate> predicateList;
    Predicate headPredicate;
public:
    Rule();
    Rule(Predicate headPredicate, vector<Predicate> predicateList);
    string toString();
    void setHeadPredicate(Predicate newHeadPredicate);
    void addPredicateToList(Predicate newPredicate);
    int getPredicateListSize();
    Predicate getPredicate(int index);
    Predicate getHeadPredicate();
};


#endif //CS_236_PROJECT_2_RULE_H
