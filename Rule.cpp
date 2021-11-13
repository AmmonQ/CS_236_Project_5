//
// Created by cppq on 9/23/2021.
//

#include "Rule.h"

Rule::Rule() {
    return;
};

Rule::Rule(Predicate headPredicate, vector<Predicate> predicateList) {
    this->headPredicate = headPredicate;
    this->predicateList = predicateList;

    return;
}

void Rule::setHeadPredicate(Predicate newHeadPredicate) {
    headPredicate = newHeadPredicate;

    return;
}

void Rule::addPredicateToList(Predicate newPredicate) {
    predicateList.push_back(newPredicate);

    return;
}

Predicate Rule::getHeadPredicate() {
    return headPredicate;
}

int Rule::getPredicateListSize() {
    return predicateList.size();
}

Predicate Rule::getPredicate(int index) {
    return predicateList.at(index);
}

string Rule::toString() {
    string finalString;

    finalString += headPredicate.toString();
    finalString += " :- ";

    for (unsigned int i = 0; i < predicateList.size(); i++) {
        finalString += predicateList.at(i).toString();

        if (i != predicateList.size() - 1) {
            finalString += ",";
        }
    }

    return finalString;
}