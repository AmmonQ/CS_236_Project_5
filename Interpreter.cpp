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

    for (const Tuple &t: joinedRelation.getRows()) {
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

void Interpreter::setDatabase(const Database &newDatabase) {
    database = newDatabase;
}

Relation Interpreter::evaluatePredicate(Predicate p) {
    Relation workingRelation = database.getRelation(p.getName());
    workingRelation.setName(p.getName());

    set<Tuple> rows = workingRelation.getRows();

    vector<int> indexes;
    vector<string> columnNames;

    map<string, int> seenMap;

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

    return workingRelation;
}

void Interpreter::evaluateAllRulesSCCs(vector<map<int, set<int>>> allSCCs) {
    bool keepGoing = true;

    int tempBefore = 0;
    int tempAfter = 0;
    int tempBefore2 = 0;
    int tempAfter2 = 0;
    int tempBeforeSelfLoop = 0;
    int tempAfterSelfLoop = 0;

    for (auto const &scc: allSCCs) {
        cout << "SCC: ";
        for (auto const &rule: scc) {
            vector<Relation> myRelations;
            if (!rule.second.empty()) {
                // make set of rules (least to greatest)
                set<int> sccRules;

                for (auto const &i: scc) {
                    sccRules.insert(i.first);
                    for (auto const &j: i.second) {
                        sccRules.insert(j);
                    }
                }

                string output;

                for (auto const &i: sccRules) {
                    output += "R" + to_string(i) + ",";
                }

                output.pop_back();
                cout << output << endl;

                bool selfLoops = false;

                for (int i = 0; i < getRuleFromNumber(rule.first).getPredicateListSize(); i++) {
                    if (getRuleFromNumber(rule.first).getHeadPredicate().getName() ==
                        getRuleFromNumber(rule.first).getPredicate(i).getName()) {
                        selfLoops = true;
                    }
                }

                if (selfLoops) {
                    int before = 0;
                    int after = 0;

                    int numPasses = 0;

                    do {
                        tempAfter2 = after;
                        tempBefore2 = before;

                        before = after;

                        for (auto const &r: rule.second) {
                            before = database.getTupleAmountInRelation(
                                    getRuleFromNumber(r).getHeadPredicate().getName());

                            Predicate myScheme;

                            for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                                if (datalogProgram.getScheme(i).getName() ==
                                    getRuleFromNumber(r).getHeadPredicate().getName()) {
                                    myScheme = datalogProgram.getScheme(i);
                                }
                            }

                            myRelations.push_back(evaluateRule(getRuleFromNumber(r), myScheme));
                        }

                        // this is for rule.first
                        Predicate firstScheme;

                        for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                            if (datalogProgram.getScheme(i).getName() ==
                                getRuleFromNumber(rule.first).getHeadPredicate().getName()) {
                                firstScheme = datalogProgram.getScheme(i);
                            }
                        }

                        myRelations.push_back(evaluateRule(getRuleFromNumber(rule.first), firstScheme));
                        after = database.getTupleAmountInRelation(
                                getRuleFromNumber(rule.first).getHeadPredicate().getName());

                        numPasses++;

                        if ((tempAfter2 == after) || (tempBefore2 == before)) {
                            keepGoing = false;
                        }
                    } while (keepGoing);

                    keepGoing = true;

                    cout << numPasses << " passes: R" << rule.first << endl;
                } else {
                    int before = 0;
                    int after = 0;

                    int numPasses = 0;

                    do {
                        tempAfter = after;
                        tempBefore = before;

                        before = after;

                        // this is for rule.second
                        for (auto const &r: rule.second) {
                            before = database.getTupleAmountInRelation(
                                    getRuleFromNumber(r).getHeadPredicate().getName());

                            Predicate myScheme;

                            for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                                if (datalogProgram.getScheme(i).getName() ==
                                    getRuleFromNumber(r).getHeadPredicate().getName()) {
                                    myScheme = datalogProgram.getScheme(i);
                                }
                            }

                            myRelations.push_back(evaluateRule(getRuleFromNumber(r), myScheme));
                        }

                        // this is for rule.first
                        Predicate firstScheme;

                        for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                            if (datalogProgram.getScheme(i).getName() ==
                                getRuleFromNumber(rule.first).getHeadPredicate().getName()) {
                                firstScheme = datalogProgram.getScheme(i);
                            }
                        }
                        after = database.getTupleAmountInRelation(
                                getRuleFromNumber(rule.first).getHeadPredicate().getName());

                        myRelations.push_back(evaluateRule(getRuleFromNumber(rule.first), firstScheme));

                        if ((tempAfter == after) || (tempBefore == before)) {
                            keepGoing = false;
                        }

                        numPasses++;
                    } while (keepGoing);

                    keepGoing = true;

                    cout << numPasses << " passes: ";

                    cout << output << endl;
                }
            } else {
                cout << "R" << rule.first << endl;

                // loop through to see if rule self loops
                bool selfLoops = false;

                for (int i = 0; i < getRuleFromNumber(rule.first).getPredicateListSize(); i++) {
                    if (getRuleFromNumber(rule.first).getHeadPredicate().getName() ==
                        getRuleFromNumber(rule.first).getPredicate(i).getName()) {
                        selfLoops = true;
                    }
                }

                if (selfLoops) {
                    int before = 0;
                    int after = 0;

                    int numPasses = 0;

                    do {
                        tempBeforeSelfLoop = before;
                        tempAfterSelfLoop = after;
                        before = after;

                        Predicate myScheme;

                        for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                            if (datalogProgram.getScheme(i).getName() ==
                                getRuleFromNumber(rule.first).getHeadPredicate().getName()) {
                                myScheme = datalogProgram.getScheme(i);
                            }
                        }

                        myRelations.push_back(evaluateRule(getRuleFromNumber(rule.first), myScheme));
                        after = database.getTupleAmountInRelation(
                                getRuleFromNumber(rule.first).getHeadPredicate().getName());

                        tempBeforeSelfLoop = after;
                        numPasses++;

                        if (((tempAfterSelfLoop == after) && (tempBeforeSelfLoop == before))) {
                            keepGoing = false;
                        }
                    } while (keepGoing);

                    keepGoing = true;

                    cout << numPasses << " passes: R" << rule.first << endl;
                } else {
                    Predicate myScheme;

                    for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                        if (datalogProgram.getScheme(i).getName() ==
                            getRuleFromNumber(rule.first).getHeadPredicate().getName()) {
                            myScheme = datalogProgram.getScheme(i);
                        }
                    }

                    myRelations.push_back(evaluateRule(getRuleFromNumber(rule.first), myScheme));
                    cout << "1 passes: R" << rule.first << endl;
                }
            }
        }
    }
}

void Interpreter::evaluateRulesSCCs(vector<map<int, set<int>>> allSCCs) {
    for (auto const &scc: allSCCs) {
        cout << "SCC: ";

        set<int> sccRules;

        for (auto const &i: scc) {
            sccRules.insert(i.first);
            for (auto const &j: i.second) {
                sccRules.insert(j);
            }
        }

        string output;

        for (auto const &i: sccRules) {
            output += "R" + to_string(i) + ",";
        }

        output.pop_back();
        cout << output << endl;

        bool keepGoing = true;
        int before = 0;
        int after = 0;
        int numPasses = 0;
        bool isSelfLoop = false;

        for (auto const &r: scc) {
            // check if it is a self loop
            for (int i = 0; i < getRuleFromNumber(r.first).getPredicateListSize(); i++) {
                if (getRuleFromNumber(r.first).getHeadPredicate().getName() == getRuleFromNumber(r.first).getPredicate(i).getName()) {
                    isSelfLoop = true;
                }
            }

            if (r.second.size() == 0 && !isSelfLoop) {
                Predicate scheme;

                for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                    if (datalogProgram.getScheme(i).getName() ==
                        getRuleFromNumber(r.first).getHeadPredicate().getName()) {
                        scheme = datalogProgram.getScheme(i);
                    }
                }

                evaluateRule(getRuleFromNumber(r.first), scheme);

                numPasses = 1;

                cout << "1 passes: ";

                cout << output << endl;
            } else if (isSelfLoop && r.second.size() != 0) {
                cout << endl << "IT'S A SELF LOOP!" << endl;
                keepGoing = true;

                before = 0;
                after = 0;

                while (keepGoing) {
                    before += database.getTupleAmountInRelation(
                            getRuleFromNumber(r.first).getHeadPredicate().getName());

                    Predicate myScheme;

                    for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                        if (datalogProgram.getScheme(i).getName() ==
                            getRuleFromNumber(r.first).getHeadPredicate().getName()) {
                            myScheme = datalogProgram.getScheme(i);
                        }
                    }

                    evaluateRule(getRuleFromNumber(r.first), myScheme);
                    after = database.getTupleAmountInRelation(
                            getRuleFromNumber(r.first).getHeadPredicate().getName());

                    numPasses++;

                    after += database.getTupleAmountInRelation(
                            getRuleFromNumber(r.first).getHeadPredicate().getName());

                    if (before == after) {
                        keepGoing = false;
                    }
                }

                cout << numPasses << " passes: R" << r.first << endl;
            } else {
                while (keepGoing) {
                    numPasses++;

                    before = 0;
                    after = 0;

                    for (auto const &rule: sccRules) {
                        before += database.getTupleAmountInRelation(
                                getRuleFromNumber(rule).getHeadPredicate().getName());

                        Predicate scheme;

                        for (int i = 0; i < datalogProgram.getSchemesSize(); i++) {
                            if (datalogProgram.getScheme(i).getName() ==
                                getRuleFromNumber(rule).getHeadPredicate().getName()) {
                                scheme = datalogProgram.getScheme(i);
                            }
                        }

                        evaluateRule(getRuleFromNumber(rule), scheme);
                        after += database.getTupleAmountInRelation(
                                getRuleFromNumber(rule).getHeadPredicate().getName());
                    }

                    if (after == before) {
                        keepGoing = false;
                        cout << numPasses << " passes: ";
                        cout << output << endl;
                    }
                }

                sccRules.clear();
            }
        }
    }
}

Rule Interpreter::getRuleFromNumber(int number) {
    return datalogProgram.getRule(number);
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