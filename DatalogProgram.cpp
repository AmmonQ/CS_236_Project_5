//
// Created by cppq on 9/23/2021.
//

#include "DatalogProgram.h"

DatalogProgram::DatalogProgram() {
    return;
}

DatalogProgram::DatalogProgram(vector<Predicate> schemes, vector<Predicate> facts, vector<Rule> rules,
                               vector<Predicate> queries) {
    this->schemes = schemes;
    this->facts = facts;
    this->rules = rules;
    this->queries = queries;
}

string DatalogProgram::toString() {
    string finalString = "";

    finalString += "Schemes(" + to_string(schemes.size()) + "):\n";

    for (unsigned int i = 0; i < schemes.size(); i++) {
        finalString += "  " + schemes.at(i).toString() + "\n";
    }

    finalString += "Facts(" + to_string(facts.size()) + "):\n";

    for (unsigned int i = 0; i < facts.size(); i++) {
        finalString += "  " + facts.at(i).toString() + ".\n";
    }

    finalString += "Rules(" + to_string(rules.size()) + "):\n";

    for (unsigned int i = 0; i < rules.size(); i++) {
        finalString += "  " + rules.at(i).toString() + ".\n";
    }

    finalString += "Queries(" + to_string(queries.size()) + "):\n";

    for (unsigned int i = 0; i < queries.size(); i++) {
        finalString += "  " + queries.at(i).toString() + "?\n";
    }

    set<string> domainSet;

    for (unsigned int i = 0; i < facts.size(); i++) {
        for (unsigned int j = 0; j < facts.at(i).getParameters().size(); j++) {
            domainSet.insert(facts.at(i).getParameters().at(j).toString());
        }
    }

    finalString += "Domain(" + to_string(domainSet.size()) + "):\n";

    for (auto i = domainSet.begin(); i != domainSet.end(); i++) {
        finalString += "  " + *i + "\n";
    }

    finalString.pop_back();

    return finalString;
}

vector<Predicate> DatalogProgram::getFacts() {
    return facts;
}

vector<Predicate> DatalogProgram::getQueries() {
    return queries;
}

vector<Predicate> DatalogProgram::getSchemes() {
    return schemes;
}

vector<Rule> DatalogProgram::getRules() {
    return rules;
}

Predicate DatalogProgram::getQuery(int index) {
    return queries.at(index);
}

Predicate DatalogProgram::getFact(int index) {
    return queries.at(index);
}

Predicate DatalogProgram::getScheme(int index) {
    return schemes.at(index);
}

Rule DatalogProgram::getRule(int index) {
    return rules.at(index);
}

int DatalogProgram::getFactsSize() {
    return facts.size();
}

int DatalogProgram::getQueriesSize() {
    return queries.size();
}

int DatalogProgram::getSchemesSize() {
    return schemes.size();
}

int DatalogProgram::getRulesSize() {
    return rules.size();
}