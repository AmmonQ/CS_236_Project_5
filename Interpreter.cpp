//
// Created by cppq on 10/11/2021.
//

#include <iostream>
#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram datalogProgram1) {
    datalogProgram = datalogProgram1;

    // loop through schemes then put them in database
    vector<Predicate> schemes = datalogProgram.getSchemes();

    for (unsigned int i = 0; i < schemes.size(); i++) {
        Relation newRelation;
        newRelation.setName(schemes.at(i).getName());

        for (int j = 0; j < schemes.at(i).getParameterSize(); j++) {
            newRelation.addHeaderAttribute(schemes.at(i).getParameter(j).toString());
        }

        database.addRelation(schemes.at(i).getName(), newRelation);
    }

    // loop through facts, make tuples from them, then insert them into relation in database
    vector<Predicate> facts = datalogProgram.getFacts();

    for (unsigned int i = 0; i < facts.size(); i++) {
        Tuple newTuple;

        for (int j = 0; j < facts.at(i).getParameterSize(); j++) {
            newTuple.addValue(facts.at(i).getParameter(j).toString());
        }

        database.getRelationByReference(facts.at(i).getName()).addTuple(newTuple);
    }
}

DatalogProgram Interpreter::getDatalogProgram() {
    return datalogProgram;
}

Relation Interpreter::evaluateRule(Rule r, Predicate scheme) {
    // Step 1 - Evaluate Predicates
    vector<Relation> ruleRelations;
    cout << r.toString() << "." << endl;

    for (int j = 0; j < r.getPredicateListSize(); j++) {
        ruleRelations.push_back(evaluatePredicate(r.getPredicate(j)));
    }

    // Step 2 - Join the relations
    Relation joinedRelation = ruleRelations.at(0);

    for (unsigned int i = 1; i < ruleRelations.size(); i++) {
        joinedRelation = joinedRelation.join(ruleRelations.at(i));
    }

    // Step 3 - Project Head Predicate's scheme columns
    Predicate headPredicate = r.getHeadPredicate();
    vector<int> indexes;

    joinedRelation = joinedRelation.project(headPredicate.getParametersString());

    // Step 4 - Rename to Header of Relation in DB
    joinedRelation = joinedRelation.rename(scheme.getParametersString());

    // Step 5 - Union with Relation in DB
    joinedRelation = joinedRelation.Union(database.getRelation(r.getHeadPredicate().getName()));

    for (const Tuple& t : joinedRelation.getRows()) {
        if (database.getRelationByReference(r.getHeadPredicate().getName()).addTuple(t)) {
            // if the tuple was added
            cout << "  ";
            for (int x = 0; x < t.getValuesSize(); x++) {
                cout << joinedRelation.getHeader().getAttribute(x) << "=";
                cout << t.getValue(x);

                if (x != t.getValuesSize() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }

    return joinedRelation;
}

void Interpreter::evaluateAllRules() {
    int before = 0;
    int after = 0;
    vector<Relation> myRelations;

    int numPasses = 0;

    cout << "Rule Evaluation" << endl;

    do {
        before = database.getTupleAmount();

        for (int j = 0; j < datalogProgram.getRulesSize(); j++) {
            // get the scheme that matches the rule's head predicate
            Predicate myScheme;

            for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                if (datalogProgram.getScheme(i).getName() == datalogProgram.getRule(j).getHeadPredicate().getName()) {
                    myScheme = datalogProgram.getScheme(i);
                }
            }

            myRelations.push_back(evaluateRule(datalogProgram.getRule(j), myScheme));
        }

        after = database.getTupleAmount();
        numPasses++;
    } while (after - before != 0);

    cout << endl << "Schemes populated after " << numPasses << " passes through the Rules." << endl << endl;
}

void Interpreter::setDatalogProgram(DatalogProgram newDatalogProgram) {
    datalogProgram = newDatalogProgram;
}

Database Interpreter::getDatabase() {
    return database;
}

void Interpreter::setDatabase(const Database& newDatabase) {
    database = newDatabase;
}

Relation Interpreter::evaluatePredicate(Predicate p) {
    Relation workingRelation = database.getRelation(p.getName());
    workingRelation.setName(p.getName());

    set<Tuple> rows = workingRelation.getRows();

    vector<int> indexes;
    vector<string> columnNames;

    map<string, int> seenMap;

    //for (Tuple t: rows) {
        for (int i = 0; i < p.getParameterSize(); i++) {
            vector<string> seenIDs;

            // this is a constant
            if (p.getParameter(i).toString()[0] == '\'') {
                workingRelation = workingRelation.select(i, p.getParameter(i).toString());
            }
                // this is a variable
            else {
                // we have seen this variable before
                if (seenMap.find(p.getParameter(i).toString()) != seenMap.end()) {
                    workingRelation = workingRelation.select(i, seenMap[p.getParameter(i).toString()]);
                } else {
                    indexes.clear();
                    columnNames.clear();
                    for (int x = 0; x < p.getParameterSize(); x++) {
                        indexes.push_back(x);
                        columnNames.push_back(p.getParameter(x).toString());
                    }

                    seenMap.insert(seenMap.begin(), pair<string, int>(p.getParameter(i).toString(), i));
                    workingRelation = workingRelation.project(indexes);
                    workingRelation = workingRelation.rename(columnNames);
                }
            }
        }
    //}

    return workingRelation;
}

void Interpreter::evaluateAllQueries() {
    vector<Predicate> queries = datalogProgram.getQueries();

    cout << "Query Evaluation" << endl;

    for (unsigned int i = 0; i < queries.size(); i++) {
        Relation newRelation = evaluatePredicate(queries.at(i));

        cout << newRelation.getName() << "(";

        bool allConstants = true;

        for (int paramIndex = 0; paramIndex < queries.at(i).getParameterSize(); paramIndex++) {
            cout << queries.at(i).getParameter(paramIndex).toString();

            if (paramIndex != queries.at(i).getParameterSize() - 1) {
                cout << ",";
            }

            if (queries.at(i).getParameter(paramIndex).toString()[0] != '\'') {
                allConstants = false;
            }
        }

        cout << ")? ";

        cout << newRelation.toString(allConstants);
    }
}